/*
 * Actor.h
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#include "Message.h"
//前方参照（インクルードガードで防がれた時のため）
class Message;

class Actor {
public:
	bool sendMessage(Message*);
	bool receiveMessage(Message*);
	bool spawnActor();
	bool changeState();

	Actor();
	virtual ~Actor();
};

#endif /* ACTOR_H_ */
