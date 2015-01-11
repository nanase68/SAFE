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

SystemActor sysActor;

/*
 *  periodic time : sec
 */
bool SystemActor::setPeriodicTask(Actor *dest, Message *msg, float periodicTime){
	TickerComposite *tc = new TickerComposite(dest, msg, periodicTime);
	TCList *tcl = new TCList;
	tcl->tc = tc;
	tcl->next = tcList;
	tcList = tcl;

	return true;
}

SystemActor::SystemActor() {
	// TODO Auto-generated constructor stub

}

SystemActor::~SystemActor() {
	// TODO Auto-generated destructor stub
}

SystemActor &SystemActor::operator <<(StateTransReqMsg *msg) {
	//debug
	printf("stateTransReq: %d\n", msg->getLabel());

	return *this;
}

SystemActor::TCList *SystemActor::tcList = 0;
