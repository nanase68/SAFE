/*
 * Runtime.h
 *
 *  Created on: 2014/12/15
 *      Author: atsushi
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

#include "tthread.h"

class Runtime {
private:
public:
	static void start();
};


class TThread {
private:
	static void starter(void *arg);
	virtual void run() = 0;
protected:
	tt_context_t context;
	TThread(bool isMainThread = false);
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


extern Runtime runtime;

#endif /* RUNTIME_H_ */
