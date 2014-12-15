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
		Message *m;
		while(!m) {
			if((m = globalPriorityQueue.dequeue())) {
			} else if((m = globalNormalQueue.dequeue())) {
			} else {
				wait(0.001);
			}
		}

		m->destination->receiveMessage(m);
	}
}
