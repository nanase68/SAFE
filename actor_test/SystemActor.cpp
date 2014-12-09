/*
 * SystemActor.cpp
 *
 *  Created on: 2014/12/09
 *      Author: Ys
 */

#include "mbed.h"
#include "SystemActor.h"
#include "Message.h"

SystemActor sysActor;

void SystemActor::autoSend(){
	//TODO lockの使い方を考える
	sysActor.sendTo(SystemActor::destination, SystemActor::message);
}

void SystemActor::beforeAttach(Actor *dest, Message *msg){
	SystemActor::destination = dest;
	SystemActor::message = msg;
	SystemActor::lock = 1;// 未使用
}

/*
 *  periodic time : sec
 */
bool SystemActor::setPeriodicTask(Actor *dest, Message *msg, double periodicTime){
	Ticker ticker;
	this->beforeAttach(dest, msg);
	ticker.attach(&SystemActor::autoSend, periodicTime); // the address of the function to be attached (flip) and the interval (2 seconds)

	return true;
}

SystemActor::SystemActor() {
	// TODO Auto-generated constructor stub

}

SystemActor::~SystemActor() {
	// TODO Auto-generated destructor stub
}

Actor *SystemActor::destination;
Message *SystemActor::message;
int SystemActor::lock;
