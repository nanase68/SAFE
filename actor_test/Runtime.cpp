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
		stack = malloc(TT_STACK_SIZE);
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

		if(m->sender->state == Actor::RUNNABLE) {
			MessageHandlerThread *handler = msgHandlerList;

			handler->msg = m;
			handler->awake(&context);
		} else {
			queue->enqueue(m);
		}
	}
}


void SchedulerThread::start() {
	run();
}


MessageHandlerThread::MessageHandlerThread() : TThread(), state(READY) {
}


void MessageHandlerThread::run() {
	while(1) {
		assert(msg != NULL);
		assert(state == READY);
		assert(msg->destination->state == Actor::RUNNABLE);

		state = BUSY;
		running = msg->sender;

		msg->destination->receiveMessage(msg);

		state = READY;

		scheduler.awake(&context);
	}
}
