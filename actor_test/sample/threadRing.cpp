/*
 * threadRing.cpp
 *
 *  Created on: 2015/02/02
 *      Author: atsushi
 */

#include <assert.h>

#include "mbed.h"
#include "Message.h"
#include "SystemActor.h"

namespace {

//static volatile int dummy;

enum LABELS {
	TEST1_START, TEST1_END
};

class Control : public Actor {
public:
	bool receiveMessage(Message *msg);
};

class Node : public Actor {
public:
	Node *next;
	Control *control;
	Timer *timer;
	Node(Control *ctrl, Timer *tmr) : control(ctrl), timer(tmr) {};
	bool receiveMessage(Message *msg);
};

bool Node::receiveMessage(Message *msg) {
	int token = msg->getLabel();
	if(token == 1) {
		timer->stop();
		msg->setLabel(TEST1_END);
		*control << *msg;
	} else {
		//printf("%d\n", token);
		//dummy = 0;
		msg->setLabel(token - 1);
		*next << *msg;
	}
	return false;
}

bool Control::receiveMessage(Message *msg) {
	static Timer timer;
	const int NODE_NUM = 512;
	const int TOKEN_NUM = 100000;
	Node *test1[NODE_NUM];
	int label = msg->getLabel();
	static Message message;
	if(label == TEST1_START) {
		puts("TEST1 start");
		for(int i=0; i<NODE_NUM; ++i) {
			test1[i] = new Node(this, &timer);
			test1[i]->next = test1[i - 1];
		}
		test1[0]->next = test1[NODE_NUM - 1];
		message.setLabel(TOKEN_NUM);
		*test1[0] << message;

		// Test1 start
		timer.reset();
		timer.start();
	} else if(label == TEST1_END) {
		printf("result: %dms\n\n\n", timer.read_ms());
	}
	return false;
}

} // unnnamed namespace

void threadRing() {
	Control control;
	Message msg(TEST1_START);
	control << msg;

	Actor::start();
}
