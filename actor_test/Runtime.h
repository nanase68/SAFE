/*
 * Runtime.h
 *
 *  Created on: 2014/12/15
 *      Author: atsushi
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include "tthread.h"

class Actor;
class Message;

class Runtime {
private:
public:
	static void start();
};


class TThread {
private:
	tt_stack_t stack;
	static void starter(void *arg);
	virtual void run() = 0;
protected:
	tt_context_t context;
	TThread(bool isMainThread = false);
	virtual ~TThread();
public:
	/** Switch to this thread */
	TThread *next;
	void awake(tt_context_t *context);
};


class MessageHandlerThread : public TThread {
private:
	void run();
public:
	Actor *running;
	Message *msg;
	Actor *waitFor;
	MessageHandlerThread();
	enum State {READY, RUNNING, WAIT} state;
	Message *waitForMessage(Actor *waitFor);
};


class SchedulerThread : public TThread {
private:
	bool stateTransFlag;
	MessageHandlerThread *msgHandlerList;
	void run();
	MessageHandlerThread *findFreeHandler();
	MessageHandlerThread *findWaitingHandler(Actor *actor);
	friend class StateControl;
public:
	MessageHandlerThread *runningHandler;
	SchedulerThread();
	void start();
};


extern Runtime runtime;
extern SchedulerThread scheduler;

#endif /* RUNTIME_H_ */
