/*
 * StateControl.cpp
 *
 *  Created on: 2015/01/08
 *      Author: atsushi
 */


#include "StateControl.h"

#include <assert.h>

#include "StateActor.h"


StateControl stateControl;


StateControl::~StateControl() {
	SACB *next;
	while(list != 0) {
		next = list->next;
		delete list;
		list = next;
	}
}

SACB *StateControl::registerStateActor(StateActor *sActor) {
	SACB *prev = 0, *sacb = list, *node = new SACB(sActor);
	if(sacb == 0) {
		list = node;
	} else {
		while(sacb != 0) {
			assert(sacb->sActor != sActor);
			prev = sacb;
			sacb = sacb->next;
		}
		prev->next = node;
	}
	return node;
}

void StateControl::removeStateActor(StateActor *sActor) {
	SACB *prev = 0, *sacb = list;

	assert(sacb != 0);

	if(sacb->sActor == sActor) {
		list = sacb->next;
		delete sacb;
		return;
	} else {
		prev = sacb;
		sacb = sacb->next;
		while(sacb != 0) {
			if(sacb->sActor == sActor) {
				prev->next = sacb->next;
				delete sacb;
				return;
			}
			prev = sacb;
			sacb = sacb->next;
		}
		assert(0);
	}
}
