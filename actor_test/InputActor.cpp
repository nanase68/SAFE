/*
 * InputActor.cpp
 *
 *  Created on: 2014/12/08
 *      Author: Ys
 */

#include "InputActor.h"
#include "Message.h"
#include "TickerComposite.h"

bool InputActor::setInterrput(Actor *dest, Message *msg, int pin){
	InterruptComposite *ic = new InterruptComposite(dest, msg, pin);
	interList->add(ic);

	return true;
}
void InputActor::rise(){
	if(interList->get() == 0){
		puts("setInterrupt before rise or fall");
		exit(1);
	}
	((InterruptComposite*) interList->get())->rise();
}
void InputActor::fall(){
	if(interList->get() == 0){
		puts("setInterrupt before rise or fall");
		exit(1);
	}
	((InterruptComposite*) interList->get())->fall();
}
InputActor::InputActor(): Actor() {
	interList = new SimpleList();
}

InputActor::~InputActor() {
	delete interList;
}

