/*
 * stateTransTest.cpp
 *
 *  Created on: 2015/01/13
 *      Author: atsushi
 */

#include <stdio.h>

#include "StateActor.h"
#include "Message.h"

class MyStateActor : public StateActor {
public:
	bool receiveMessage(Message *m);
	void stateTrans(int prev, int next);
};
bool MyStateActor::receiveMessage(Message *m) {
	printf("state is %d\n", gState);

	return false;
}

void MyStateActor::stateTrans(int prev, int next) {
	puts("!!state Trans!!");
	this->sendTo(this, new Message);
}

void stateTransTest() {
	MyStateActor a1, a2;
	a1.gState = 10;
	a2.gState = 20;

	Actor::start();
}
