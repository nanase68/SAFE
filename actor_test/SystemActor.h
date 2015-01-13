/*
 * SystemActor.h
 *
 *  Created on: 2014/12/09
 *      Author: Ys
 */

#ifndef SYSTEMACTOR_H_
#define SYSTEMACTOR_H_

#include "Actor.h"
#include "Message.h"
#include "SimpleList.h"
class TickerComposite;

class SystemActor: public Actor {
private:
	SimpleList *tcList;
	SimpleList *tocList;

public:
	bool setPeriodicTask(Actor *dest, Message *msg, float periodicTime);
	void timeoutCallback(Actor *dest, Message *msg);
	bool receiveMessage(Message* m);

	SystemActor();
	virtual ~SystemActor();
};

extern SystemActor sysActor;

#endif /* SYSTEMACTOR_H_ */
