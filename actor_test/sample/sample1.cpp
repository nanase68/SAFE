/*
 * sample1.cpp
 *
 *  Created on: 2014/12/09
 *      Author: atsushi
 */

#include <iostream>

#include "Actor.h"
#include "Message.h"

#include "mbed.h"

namespace {

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
	sendMessage(m);

	return false;
}

}

void sample1() {
	MyActor a;
	Message m(&a, &a);
	a.sendMessage(&m);

	Actor::start();
	return;
}

