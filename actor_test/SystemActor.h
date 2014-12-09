/*
 * SystemActor.h
 *
 *  Created on: 2014/12/09
 *      Author: Ys
 */

#ifndef SYSTEMACTOR_H_
#define SYSTEMACTOR_H_

#include "Actor.h"

class SystemActor: public Actor {
private:
	static Actor *destination;
	static Message *message;
	static int lock;

public:
	static void autoSend();
	void beforeAttach(Actor *dest, Message *msg);
	bool setPeriodicTask(Actor *dest, Message *msg, double periodicTime);

	SystemActor();
	virtual ~SystemActor();
};

extern SystemActor sysActor;

#endif /* SYSTEMACTOR_H_ */
