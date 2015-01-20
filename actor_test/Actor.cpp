/*
 * Actor.cpp
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */
#include "mbed.h"
#include "Actor.h"
#include "SystemActor.h"
#include "Message.h"
#include "GlobalQueue.h"
#include "Runtime.h"

using namespace std;


bool Actor::receiveMessage(Message* m){
	return false;
}

bool Actor::sendToQueue(Actor *dest, Message *m, GlobalQueue *gqueue){
	m->sender = this;
	m->destination = dest;
	gqueue->enqueue(m);
	return true;
}

bool Actor::sendTo(Actor *dest, Message* m){
	this->sendToQueue(dest, m, &globalNormalQueue);
	return true;
}

Message *Actor::sendWait(Actor *dest, Message* m){
	this->sendTo(dest, m);
	MessageHandlerThread *handler = scheduler.runningHandler;
	// ここでこの処理をttswitchし、次に呼ばれるまで待機状態にする
	return handler->waitForMessage(dest);
}

bool Actor::waitTimeout(float time){
	// floatをvoid*にキャスト
	Message* m = new Message(sysCmd::WAIT, *(void**)&time);
	this->sendWait(&sysActor, m);

	delete m;
	return true;
}

bool Actor::sendToPriorityQueue(Actor *dest, Message *m){
	this->sendToQueue(dest, m, &globalPriorityQueue);
	return true;
}


bool Actor::start(){
	runtime.start();

	return true;
}

Actor::Actor() : state(RUNNABLE) {
	// TODO Auto-generated constructor stub

}

Actor::~Actor() {
	// TODO Auto-generated destructor stub
}


Actor &Actor::operator<<(Message &m) {
	MessageHandlerThread *th = scheduler.runningHandler;
	Actor *sender = (th) ? th->running : &sysActor;

	sender->sendTo(this, &m);

	return *this;
}
