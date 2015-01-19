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
void SystemActor::timeoutCallback(Actor* dest, Message* m) {
	// MEMO: ハンドラモードでprintfやdelete, newをしてはいけない！
	sendToPriorityQueue(dest, m);
}
bool SystemActor::receiveMessage(Message* m) {
	int label = m->getLabel();
	if (label == sysCmd::WAIT) {
		float* waitTime = (float*) m->getContent();
		TimeoutComposite *tc = new TimeoutComposite(m->sender, m, *waitTime);
		tocList->add(tc);
		puts("wait");
	}else if(label == sysCmd::DELETE_TOC){
		puts("remove");
		delete (TimeoutComposite*)(tocList->get());
		tocList->remove();
	}
	return true;
}

SystemActor::SystemActor() {
	msg_deleteToc = new Message(sysCmd::DELETE_TOC);
	SystemActor::tcList = new SimpleList();
	SystemActor::tocList = new SimpleList();
}

SystemActor::~SystemActor() {
	delete msg_deleteToc;
	delete SystemActor::tcList;
	delete SystemActor::tocList;
}
