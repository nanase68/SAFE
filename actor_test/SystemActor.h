/*
 * SystemActor.h
 *
 *  Created on: 2014/12/09
 *      Author: Ys
 */

#ifndef SYSTEMACTOR_H_
#define SYSTEMACTOR_H_

#include "mbed.h"
#include "Actor.h"
#include <vector>
class TickerComposite;

class SystemActor: public Actor {
private:
	static vector<TickerComposite*> tcVector;

public:
	bool setPeriodicTask(Actor *dest, Message *msg, float periodicTime);

	void makeTicker();

	SystemActor();
	virtual ~SystemActor();
};

extern SystemActor sysActor;

#endif /* SYSTEMACTOR_H_ */
