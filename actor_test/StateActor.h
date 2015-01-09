/*
 * StateActor.h
 *
 *  Created on: 2015/01/08
 *      Author: atsushi
 */

#ifndef STATEACTOR_H_
#define STATEACTOR_H_


#include "Actor.h"

class SACB;

class StateActor : public Actor {
public:
	int gState; /* global state */
	SACB *sacb; /* StateActor Control Block */

	StateActor();
	virtual ~StateActor();

	virtual void stateTrans(int prev, int next);
	bool sendToQueue(Actor *dest, Message *m, GlobalQueue *gqueue);
};


#endif /* STATEACTOR_H_ */
