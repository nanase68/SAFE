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


class SchedulerThread {
private:
	tt_context_t context;
	static void run(void *arg);
public:
	SchedulerThread();
	void awake(tt_context_t *oldContext);
};


extern Runtime runtime;

#endif /* RUNTIME_H_ */
