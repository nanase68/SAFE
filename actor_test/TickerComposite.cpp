/*
 * TickerComposit.cpp
 *
 *  Created on: 2014/12/10
 *      Author: Ys
 */

#include "TickerComposite.h"
#include "mbed.h"
#include "Message.h"
#include "SystemActor.h"

void TickerComposite::autoSend(){
	sysActor.sendTo(TickerComposite::destination, TickerComposite::message);
}

TickerComposite::TickerComposite(Actor *dest, Message *msg, float periodicTime){
	TickerComposite::ticker = new Ticker();
	TickerComposite::destination = dest;
	TickerComposite::message = msg;

	TickerComposite::ticker->attach(this, &TickerComposite::autoSend, periodicTime);
}

TickerComposite::~TickerComposite(){
	delete ticker;
}
