/*
 * stateLcdSample1.cpp
 *
 *  Created on: 2015/01/26
 *      Author: atsushi
 */

#include <assert.h>

#include "mbed.h"
#include "Message.h"
#include "StateActor.h"
#include "SystemActor.h"

namespace {

enum Cmd {
	DO, RIGHT, LEFT
};

class LedActor : public StateActor {
public:
	Actor *left, *right;
	DigitalOut &led;
	LedActor(DigitalOut &led) : led(led) {};
	bool receiveMessage(Message* m);
};

class Boss : public StateActor {
public:
	Actor *right;
	Actor *left;
	bool reqFlag;
	Boss() : reqFlag(false) {};
	bool receiveMessage(Message *msg);
	void stateTrans(int prev, int next);
};
class InputActor : public StateActor {
public:
	InterruptIn joyL;
	InterruptIn joyR;
	Message msgL;
	Message msgR;
	InputActor();
	void sendL();
	void sendR();
	bool receiveMessage(Message *msg);
};
//=================

bool LedActor::receiveMessage(Message *msg) {
	led = 1; //点灯
	this->waitTimeout(1.0);
	led = 0; //消灯
	if(this->gState == RIGHT) {
		*this->right << *msg;
	} else if(this->gState == LEFT) {
		*this->left << *msg;
	}
}


bool Boss::receiveMessage(Message *msg) {
	switch(msg->getLabel()) {
	case RIGHT:
		sysActor << stateTransReq(RIGHT);
		reqFlag = true;
		break;
	case LEFT:
		sysActor << stateTransReq(LEFT);
	case DO:
		if (reqFlag) {
			;
		} else if(this->gState == RIGHT) {
			*right << *msg;
		} else if(this->gState == LEFT) {
			*left << *msg;
		}
	}
}
void Boss::stateTrans(int prev, int next) {
	this->reqFlag = false;
	if(next == RIGHT) {
		*right << *(new Message(DO));
	} else if(next == LEFT) {
		*left << *(new Message(DO));
	}
}

InputActor::InputActor() :
		joyL(p12), joyR(p15), msgL(LEFT), msgR(RIGHT)
{
	joyL.rise(this, &InputActor::sendL);
	joyR.rise(this, &InputActor::sendR);
};

void InputActor::sendL() {
	this->sendTo(this, &msgL);
}

void InputActor::sendR() {
	this->sendTo(this, &msgR);
}

bool InputActor::receiveMessage(Message *msg) {
	if(msg == &msgL) {
		puts("IN:msgL");
		sysActor << stateTransReq(LEFT);
	} else if(msg == &msgR) {
		puts("IN:msgR");
		sysActor << stateTransReq(RIGHT);
	} else {
		assert(0);
	}
	return true;
}

class TestActor : public Actor {
public:
	DigitalOut led;
	TestActor() : led(LED1) {};
	bool receiveMessage(Message *msg){
		puts("receive!!");
		led = !led;
		waitTimeout(1.0);
		return false;
	}
};


}  // unnamed namespace

void stateLcdSample1() {
/*	DigitalOut led1(LED1);
	DigitalOut led2(LED2);
	DigitalOut led3(LED3);
	DigitalOut led4(LED4);

	Boss boss;
	LedActor ledA[4] = {led1, led2, led3, led4};
	InputActor in;

	for(int i=0; i<4; ++i) {
		ledA[i].left = ledA + i - 1;
		ledA[i].right = ledA + i + 1;
	}
	ledA[0].left = &boss;
	ledA[3].right = &boss;
	boss.left = ledA + 3;
	boss.right = ledA;*/

	TestActor test;
	Message m;

	test << m;
	Actor::start();
}
