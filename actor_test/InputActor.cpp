/*
 * InputActor.cpp
 *
 *  Created on: 2014/12/08
 *      Author: Ys
 */

#include "InputActor.h"
#include "TickerComposite.h"

bool InputActor::setInterrput(Message *msg, int pin){
	InterruptComposite *ic = new InterruptComposite(this, msg, pin);
	interList->add(ic);

	return true;
}
InputActor::InputActor(): Actor() {
	interList = new SimpleList();
}

InputActor::~InputActor() {
	delete interList;
}

