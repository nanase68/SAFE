/*
 * StateActor.cpp
 *
 *  Created on: 2015/01/08
 *      Author: atsushi
 */

#include "StateActor.h"

#include "StateControl.h"

StateActor::StateActor() : gState(stateControl.getCurrentState()) {
	sacb = stateControl.registerStateActor(this);
}

StateActor::~StateActor() {
	stateControl.removeStateActor(this);
}
