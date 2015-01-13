/*
 * StateControl.h
 *
 *  Created on: 2015/01/08
 *      Author: atsushi
 */

#ifndef STATECONTROL_H_
#define STATECONTROL_H_


class StateActor;

/* StateActor Control Block */
class SACB {
public:
	StateActor *sActor;
	SACB *next;

	SACB(StateActor *sActor) : sActor(sActor), next(0) {};
};

class StateControl {
private:
	SACB *list;
	int currentState;
	bool reqFlag;
	int request;
public:
	StateControl() : list(0),currentState(0), reqFlag(false), request(0) {};
	virtual ~StateControl();

	SACB *getList() { return list; };
	SACB *registerStateActor(StateActor *sActor);
	void removeStateActor(StateActor *sActor);
	void stateTransReq(int state);
	void stateTransition();
};

extern StateControl stateControl;

#endif /* STATECONTROL_H_ */
