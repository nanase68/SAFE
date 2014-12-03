/*
 * Message.h
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Actor.h"
//前方参照（インクルードガードで防がれた時のため）
class Actor;

class Message {
protected:
	Actor *sender, *destination;

public:
	bool dealMessage(void);

	Message();
	Message(Actor*, Actor*);
	virtual ~Message();
};

#endif /* MESSAGE_H_ */
