/*
 * Runtime.cpp
 *
 *  Created on: 2014/12/12
 *      Author: atsushi
 */

#include "mbed.h"

#include "Runtime.h"
#include "GlobalQueue.h"
#include "Actor.h"
#include "Message.h"
#include "tthread.h"

Runtime runtime;
tt_context_t mainContext;

void Runtime::start() {
	SchedulerThread th;
	th.awake(&mainContext);
}


SchedulerThread::SchedulerThread() {
	tt_stack_t stack = malloc(TT_STACK_SIZE);
	SchedulerThread::context =
			tt_new_context(stack + TT_STACK_DEPTH, &SchedulerThread::run, NULL);
}


void SchedulerThread::run(void* arg) {
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
			m->destination->receiveMessage(m);
		} else {
			queue->enqueue(m);
		}
	}
}


void SchedulerThread::awake(tt_context_t *oldContext) {
	tt_swtch(oldContext, context);
}

