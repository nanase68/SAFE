/*
 * sample1.cpp
 *
 *  Created on: 2014/12/09
 *      Author: atsushi
 */

#include <iostream>

#include "Actor.h"
#include "Message.h"
#include "SystemActor.h"

#include "mbed.h"

namespace {

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

class MyActor : public Actor {
public:
	bool receiveMessage(Message *m);
	~MyActor() {};
} actor;

bool MyActor::receiveMessage(Message *m) {
	cout << "receiveMessage" << endl;

	if((led2 == 0) && (led3 == 0) && (led4 == 0)){
		led2 = 1;
	}else{
		int temp = led4;
		led4 = led3;
		led3 = led2;
		led2 = temp;
	}

	//同じメッセージ使い回し（手抜き）
	sendTo(this, m);

	return false;
}

class MyActor2 : public Actor{
public:
	bool receiveMessage(Message *m);
} actor2;

bool MyActor2::receiveMessage(Message *m){
	cout << "receiveMessage2" << endl;

	led1 = !led1;

	this->sendTo(this, m);

	return false;
}

}// namespace

void sample1() {
	MyActor a;
	MyActor2 a2;
	Message m, m2;
	a.sendTo(&a, &m);
	//a2.sendTo(&a2, &m2);
	sysActor.setPeriodicTask(&a2, &m2, 2.0);

	cout << "Start!!" << endl;
	Actor::start();
	return;
}

