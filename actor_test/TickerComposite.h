/*
 * TickerComposit.h
 *
 *  Created on: 2014/12/10
 *      Author: Ys
 */

#ifndef TICKERCOMPOSIT_H_
#define TICKERCOMPOSIT_H_

#include "mbed.h"
class Actor;
class Message;


// 抽象クラス
class BaseComposite{
public:
	Actor *destination;
	Message *message;

	virtual void autoSend() = 0; //純粋仮想関数

	BaseComposite(Actor *dest, Message *msg): destination(dest), message(msg){};
	virtual ~BaseComposite(){}
};

class TickerComposite: BaseComposite{
public:
	mbed::Ticker *ticker;

	void autoSend();

	TickerComposite(Actor *dest, Message *msg, float periodicTime);
	~TickerComposite();
};

class TimeoutComposite: BaseComposite{
public:
	mbed::Timeout *timeout;

	void autoSend();

	TimeoutComposite(Actor *dest, Message *msg, float waitTime);
	~TimeoutComposite();
};

class InterruptComposite: BaseComposite{
private:
	mbed::InterruptIn interrputIn;
public:

	void autoSend();

	void rise();
	void fall();

	InterruptComposite(Actor *dest, Message *msg, PinName pin): BaseComposite(dest, msg), interrputIn(pin){};
};
#endif /* TICKERCOMPOSIT_H_ */
