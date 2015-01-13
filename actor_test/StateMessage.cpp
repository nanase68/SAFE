/*
 * StateMessage.cpp
 *
 *  Created on: 2015/01/11
 *      Author: atsushi
 */

#include "StateMessage.h"


StateTransReqMsg *stateTransReq(int state) {
	return new StateTransReqMsg(state);
}
