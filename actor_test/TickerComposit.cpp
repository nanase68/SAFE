/*
 * TickerComposit.cpp
 *
 *  Created on: 2014/12/10
 *      Author: Ys
 */

#include "TickerComposit.h"
#include "mbed.h"
#include "Message.h"
#include "SystemActor.h"

void TickerComposit::autoSend(){
	sysActor.sendTo(TickerComposit::destination, TickerComposit::message);
}

TickerComposit::TickerComposit(Actor *dest, Message *msg, float periodicTime){
	TickerComposit::ticker = new Ticker();
	TickerComposit::destination = dest;
	TickerComposit::message = msg;

	TickerComposit::ticker->attach(this, &TickerComposit::autoSend, periodicTime);
}

TickerComposit::~TickerComposit(){
	delete ticker;
}
