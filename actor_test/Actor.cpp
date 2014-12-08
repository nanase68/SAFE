/*
 * Actor.cpp
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */
#include "mbed.h"
#include "Actor.h"
#include "Message.h"
#include "GlobalQueue.h"

#include <stdio.h>
#include <iostream>

using namespace std;


Ticker ticker;

DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);


bool Actor::receiveMessage(Message* m){
	// TODO かく
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
	gqueue.enqueue(m);


	return false;

}

bool Actor::sendMessage(Message* m){
	gqueue.enqueue(m);
	return true;
}


bool Actor::start(){
	while(1){
		gqueue.checkQueue();

		wait(1);
		//wait(0.01); // 0.01 sec
	}
	return true;
}

Actor::Actor() {
	// TODO Auto-generated constructor stub

}

Actor::~Actor() {
	// TODO Auto-generated destructor stub
}

