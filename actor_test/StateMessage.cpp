/*
 * StateMessage.cpp
 *
 *  Created on: 2015/01/11
 *      Author: atsushi
 */

#include "StateMessage.h"


StateChangeReqMsg *stateChangeReq(int state) {
	return new StateChangeReqMsg(state);
}
