/*
 * TickerComposit.cpp
 *
 *  Created on: 2014/12/10
 *      Author: Ys
 */

#include "mbed.h"
#include "Message.h"
#include "SystemActor.h"
#include "TickerComposite.h"

// MEMO: ハンドラモードでprintfやdelete, newをしてはいけない！
/*
 *
 */
void TickerComposite::autoSend(){
	sysActor.sendToPriorityQueue(TickerComposite::destination, TickerComposite::message);
}
TickerComposite::TickerComposite(Actor *dest, Message *msg, float periodicTime): BaseComposite(dest, msg){
	TickerComposite::ticker = new Ticker();
	TickerComposite::ticker->attach(this, &TickerComposite::autoSend, periodicTime);
}

TickerComposite::~TickerComposite(){
	delete ticker;
}

/*
 *
 */
void TimeoutComposite::autoSend(){
	sysActor.sendToPriorityQueue(TimeoutComposite::destination, TimeoutComposite::message);
	sysActor.sendTo(&sysActor, sysActor.getMsgDeleteToc());
}
TimeoutComposite::TimeoutComposite(Actor *dest, Message *msg, float waitTime): BaseComposite(dest, msg){
	TimeoutComposite::timeout = new Timeout();
	TimeoutComposite::timeout->attach(this, &TimeoutComposite::autoSend, waitTime);
}

TimeoutComposite::~TimeoutComposite(){
	delete timeout;
}

/*
 *
 */
void InterruptComposite::autoSend(){
	sysActor.sendToPriorityQueue(InterruptComposite::destination, InterruptComposite::message);
}
void InterruptComposite::rise(){
	InterruptComposite::interrputIn.rise(this, &InterruptComposite::autoSend);
}
void InterruptComposite::fall(){
	InterruptComposite::interrputIn.fall(this, &InterruptComposite::autoSend);
}

