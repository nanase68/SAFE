/*
 * Actor.h
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#ifndef ACTOR_H_
#define ACTOR_H_

//前方参照（インクルードガードで防がれた時のため）
class Message;

class Actor {
public:
	bool sendMessage(Message*);
	virtual bool receiveMessage(Message*);
	bool spawnActor();
	bool changeState();

	void checkQueue();
	static bool start();

	Actor();
	virtual ~Actor();
};

#endif /* ACTOR_H_ */
