/*
 * SystemActor.cpp
 *
 *  Created on: 2014/12/09
 *      Author: Ys
 */

#include "mbed.h"
#include "SystemActor.h"
#include "Message.h"
#include "TickerComposite.h"
#include "StateMessage.h"
#include "StateControl.h"

SystemActor sysActor;

/*
 *  periodic time : sec
 */
bool SystemActor::setPeriodicTask(Actor *dest, Message *msg,
		float periodicTime) {
	TickerComposite *tc = new TickerComposite(dest, msg, periodicTime);
	// MEMO: このnewに対応するdeleteはいまのところない
	tcList->add(tc);
	return true;
}

bool SystemActor::receiveMessage(Message* m) {
	int label = m->getLabel();
	if (label == sysCmd::WAIT) {
		void *content = m->getContent();
		// void*からfloatにキャスト
		float waitTime = *(float*) &content;
		TimeoutComposite *tc = new TimeoutComposite(m->sender, m, waitTime);
		tocList->add(tc);
	}else if(label == sysCmd::DELETE_TOC){
		delete (TimeoutComposite*)(tocList->get());
		tocList->remove();
	}
	return true;
}

SystemActor::SystemActor() {
	// FIX: Timeoutの作成順と終了順が入れ違った場合、意図されてないtocが消されてしまう
	msg_deleteToc = new Message(sysCmd::DELETE_TOC);
	SystemActor::tcList = new SimpleList();
	SystemActor::tocList = new SimpleList();
}

SystemActor::~SystemActor() {
	delete msg_deleteToc;
	delete SystemActor::tcList;
	delete SystemActor::tocList;
}

SystemActor &SystemActor::operator <<(StateTransReqMsg *msg) {
	//debug
	printf("stateTransReq: %d\n", msg->getLabel());

	stateControl.stateTransReq(msg->getLabel());

	return *this;
}
