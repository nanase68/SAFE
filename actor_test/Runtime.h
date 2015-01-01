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
	void awake(tt_context_t *context);
};


class SchedulerThread : public TThread {
private:
	void run();
public:
	SchedulerThread();
	void start();
};


class MessageHandlerThread : public TThread {
private:
	void run();
public:
	Actor *running;
	Message *msg;
	MessageHandlerThread();
	enum State {READY, BUSY} state;
};


extern Runtime runtime;
extern SchedulerThread scheduler;

#endif /* RUNTIME_H_ */
