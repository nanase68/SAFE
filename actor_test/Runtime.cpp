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

Runtime runtime;

void Runtime::start() {
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
