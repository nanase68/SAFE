/*
 * StateMessage.h
 *
 *  Created on: 2015/01/11
 *      Author: atsushi
 */

#ifndef STATEMESSAGE_H_
#define STATEMESSAGE_H_

#include "Message.h"

class StateChangeReqMsg : public Message {
public:
	StateChangeReqMsg(int state) : Message(state) {};
	virtual ~StateChangeReqMsg();
};

StateChangeReqMsg *stateChangeReq(int state);


#endif /* STATEMESSAGE_H_ */
