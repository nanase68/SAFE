/*
 * InputActor.h
 *
 *  Created on: 2014/12/08
 *      Author: Ys
 */

#ifndef INPUTACTOR_H_
#define INPUTACTOR_H_

#include "Actor.h"
#include "SimpleList.h"

class InputActor: public Actor {
private:
	SimpleList *interList;
public:
	bool setInterrput(Actor *dest, Message *msg, int pin);

	void rise();
	void fall();

	InputActor();
	virtual ~InputActor();
};

#endif /* INPUTACTOR_H_ */
