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


using namespace std;


bool Actor::receiveMessage(Message* m){
	return false;
}

bool Actor::sendToQueue(Actor *dest, Message *m, GlobalQueue gqueue){
	m->sender = this;
	m->destination = dest;
	gqueue.enqueue(m);
	return true;
}

bool Actor::sendTo(Actor *dest, Message* m){
	this->sendToQueue(dest, m, globalNormalQueue);
	return true;
}


bool Actor::start(){
	while(1){
		if(globalPriorityQueue.checkQueue()){
		}else if(globalNormalQueue.checkQueue()){
		}

		wait(0.01); // 0.01 sec
	}
	return true;
}

Actor::Actor() {
	// TODO Auto-generated constructor stub

}

Actor::~Actor() {
	// TODO Auto-generated destructor stub
}

