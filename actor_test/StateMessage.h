/*
 * StateMessage.h
 *
 *  Created on: 2015/01/11
 *      Author: atsushi
 */

#ifndef STATEMESSAGE_H_
#define STATEMESSAGE_H_

#include "Message.h"

class StateTransReqMsg : public Message {
public:
	StateTransReqMsg(int state) : Message(state) {};
	virtual ~StateTransReqMsg() {};
};

StateTransReqMsg *stateTransReq(int state);


#endif /* STATEMESSAGE_H_ */
