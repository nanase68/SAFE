/*
 * stateTransTest.cpp
 *
 *  Created on: 2015/01/13
 *      Author: atsushi
 */

#include <stdio.h>

#include "StateActor.h"
#include "Message.h"
#include "SystemActor.h"

class MyStateActor : public StateActor {
private:
	const bool isMaster;
public:
	MyStateActor(bool isMaster) : isMaster(isMaster) {};
	bool receiveMessage(Message *m);
	void stateTrans(int prev, int next);
};
bool MyStateActor::receiveMessage(Message *m) {
	printf("state is %d\n", gState);

	if(isMaster) {
		sysActor << stateTransReq(gState + 10);
	}

	return false;
}

void MyStateActor::stateTrans(int prev, int next) {
	puts("!!state Trans!!");
	this->sendTo(this, new Message);
}

void stateTransTest() {
	static MyStateActor a1(true), a2(false);
	static Message m;
	a1.gState = 10;
	a2.gState = 20;

	a1 << m;

	Actor::start();
}
