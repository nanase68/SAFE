/*
 * Runtime.cpp
 *
 *  Created on: 2014/12/12
 *      Author: atsushi
 */

#include <assert.h>

#include "mbed.h"

#include "Runtime.h"
#include "GlobalQueue.h"
#include "Actor.h"
#include "Message.h"
#include "tthread.h"

Runtime runtime;
SchedulerThread scheduler;


void Runtime::start() {
	scheduler.start();
}


TThread::TThread(bool isMainThread) : next(NULL) {
	if(isMainThread) {
		context = NULL;
	} else {
		printf("malloc in TThread... ");
		stack = (tt_stack_t) malloc(TT_STACK_SIZE);
		printf("OK!\n");
		context = tt_new_context(stack + TT_STACK_DEPTH, &starter, this);
	}
}


TThread::~TThread() {
	free(stack);
}


void TThread::starter(void *thisThread) {
	TThread *th = (TThread *)thisThread;
	th->run();
}


void TThread::awake(tt_context_t *oldContext) {
	tt_swtch(oldContext, context);
}


SchedulerThread::SchedulerThread() :
		TThread(true),
		msgHandlerList(new MessageHandlerThread) {
}


MessageHandlerThread *SchedulerThread::findFreeHandler() {
	MessageHandlerThread *th = msgHandlerList, *prev = NULL;

	if(th == NULL) {
		return (msgHandlerList = new MessageHandlerThread);
	}
	while(th != NULL) {
		if(th->state == MessageHandlerThread::READY) {
			return th;
		} else {
			prev = th;
			th = (MessageHandlerThread *)(prev->next);
		}
	}
	th = new MessageHandlerThread;
	prev->next = th;
	return th;
}


MessageHandlerThread *SchedulerThread::findWaitingHandler(Actor *actor) {
	MessageHandlerThread *th = msgHandlerList;

	while(th != NULL) {
		if(th->running == actor) {
			break;
		} else {
			th = (MessageHandlerThread *)(th->next);
		}
	}
	return th;
}


void SchedulerThread::run() {
	while(1) {
		Message *m = NULL;
		GlobalQueue *queue;
		while(!m) {
			if((m = globalPriorityQueue.dequeue())) {
				queue = &globalPriorityQueue;
			} else if((m = globalNormalQueue.dequeue())) {
				queue = &globalNormalQueue;
			} else {
				wait(0.001);
			}
		}

		if(m->destination->state == Actor::RUNNABLE) {
			runningHandler = findFreeHandler();
			runningHandler->msg = m;

			runningHandler->awake(&context);

			runningHandler = NULL;
		} else if(m->destination->state == Actor::SENDWAIT) {
			MessageHandlerThread *waitingHandler;

			waitingHandler = findWaitingHandler(m->destination);

			if(waitingHandler->waitFor == m->sender) {
				waitingHandler->awake(&context);
			} else {
				queue->enqueue(m);
			}
		} else {
			queue->enqueue(m);
		}
	}
}


void SchedulerThread::start() {
	run();
}


MessageHandlerThread::MessageHandlerThread() :
		TThread(), waitFor(NULL), state(READY) {
}


void MessageHandlerThread::run() {
	while(1) {
		assert(msg != NULL);
		assert(state == READY);
		assert(msg->destination->state == Actor::RUNNABLE);

		state = RUNNING;
		running = msg->destination;

		msg->destination->receiveMessage(msg);

		state = READY;

		scheduler.awake(&context);
	}
}


Message *MessageHandlerThread::waitForMessage(Actor *waitFor) {
	state = WAIT;
	this->waitFor = waitFor;
	running->state = Actor::SENDWAIT;

	scheduler.awake(&context);

	state = RUNNING;
	this->waitFor = NULL;
	running->state = Actor::RUNNABLE;

	return msg;
}
