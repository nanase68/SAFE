/*
 * sendWaitSample.cpp
 *
 *  Created on: 2015/01/03
 *      Author: atsushi
 */

#include <assert.h>

#include "Actor.h"
#include "Message.h"
#include "SystemActor.h"

#include "mbed.h"

namespace {


enum Order {TurnOn, TurnOff};
enum ledState {LedIsOn, LedIsOff};

class BossActor;
class WorkerActor;

class BossActor : public Actor {
private:
	DigitalOut &led;
	WorkerActor *w[3];
public:
	BossActor(DigitalOut &led) : led(led) {};
	bool receiveMessage(Message *m);
	void setWorkers(WorkerActor *w0, WorkerActor *w1, WorkerActor *w2) {
		w[0] = w0; w[1] = w1; w[2] = w2;
	}
};

class WorkerActor : public Actor {
private:
	int id;
	DigitalOut &led;
	BossActor &boss;
public:
	WorkerActor(int id, DigitalOut &led, BossActor &boss) :
		id(id), led(led), boss(boss) {};
	bool receiveMessage(Message *m);
};


bool BossActor::receiveMessage(Message *m) {
	static int timing[3] = {1, 2, 3};
	static bool isOn[3] = {};
	static int count = 0;
	static MessageInt mTurnOn(NULL, NULL, TurnOn);
	static MessageInt mTurnOff(NULL, NULL, TurnOff);

	// Sender is WorkerActor
	for(int i=0; i < 3; ++i) {
		if(m->sender == w[i]) {
			isOn[i] = true;
			delete m;
			return true;
		}
	}

	// Sender is SystemActor
	++count;
	printf("count: %04d\n", count);

	led = !led;

	for(int i=0; i < 3; ++i) {
		if(count % timing[i] == 0) {
			MessageInt *msg = new MessageInt;
			*msg = isOn[i] ? mTurnOff : mTurnOn;
			sendTo(w[i], msg);
			if(isOn[i]) { isOn[i] = false; }
		}
	}

	return true;
}

bool WorkerActor::receiveMessage(Message *m) {
	static MessageInt ledIsOn;
	Message *send;

	int order = (((MessageInt *)m)->get_content());
	if(order == TurnOn) {
		led = 1;

		send = new MessageInt;
		*send = ledIsOn;

		printf("Worker%d: sendWait\n", id);
		//Wait until Boss order me to turn off
		MessageInt *re = (MessageInt *) sendWait(&boss, send);
		printf("Worker%d: receive\n", id);

		//assert(re->get_content() == TurnOff);
		led = 0;
	}

	delete m;
	return true;
}


} // namespace (unnamed)

void sendWaitSample() {
	DigitalOut led1(LED1);
	DigitalOut led2(LED2);
	DigitalOut led3(LED3);
	DigitalOut led4(LED4);

	BossActor b(led1);
	WorkerActor w0(0, led2, b);
	WorkerActor w1(1, led3, b);
	WorkerActor w2(2, led4, b);
	Message m, m2;
	Actor a;
	//a.sendTo(&b, &m2);

	b.setWorkers(&w0, &w1, &w2);

	sysActor.setPeriodicTask(&b, &m, 1.0);

	printf("Start!\n");
	Actor::start();

	return;
}
