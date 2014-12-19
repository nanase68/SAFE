/*
 * Actor.h
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#ifndef ACTOR_H_
#define ACTOR_H_

class Message;
class GlobalQueue;

class Actor {
private:
	enum State { RUNNABLE, SENDWAIT } state;
	friend class RuntimeThread;
public:
	bool sendToQueue(Actor *dest, Message *m, GlobalQueue *gqueue);
	bool sendTo(Actor *dest, Message *m);
	bool sendToPriorityQueue(Actor *dest, Message *m);
	virtual bool receiveMessage(Message*);
	bool spawnActor();
	bool changeState();

	void checkQueue();
	static bool start();

	Actor();
	virtual ~Actor();
};

#endif /* ACTOR_H_ */
