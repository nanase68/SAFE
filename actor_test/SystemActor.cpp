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
bool SystemActor::setPeriodicTask(Actor *dest, Message *msg, float periodicTime){
	TickerComposite *tc = new TickerComposite(dest, msg, periodicTime);
	// MEMO: このnewに対応するdeleteはいまのところない
	tcList->add(tc);
	return true;
}
void SystemActor::timeoutCallback(Actor* dest, Message* m){
	// MEMO: ハンドラモードでprintfやdelete, newをしてはいけない！
	sendToPriorityQueue(dest, m);
	//delete tocList->get();
	//tocList->remove();
}
bool SystemActor::receiveMessage(Message* m){
	//puts("system actor receive message");
	double waitTime = ((MessageDouble*)m)->get_content();
	TimeoutComposite *tc = new TimeoutComposite(m->sender, m, (float)waitTime);
	tocList->add(tc);

	return true;
}

SystemActor::SystemActor() {
	// TODO Auto-generated constructor stub

}

SystemActor::~SystemActor() {
	// TODO Auto-generated destructor stub
}
