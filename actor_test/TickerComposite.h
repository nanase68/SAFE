/*
 * TickerComposit.h
 *
 *  Created on: 2014/12/10
 *      Author: Ys
 */

#ifndef TICKERCOMPOSIT_H_
#define TICKERCOMPOSIT_H_

namespace mbed{
	class Ticker;
	class Timeout;
}
class Actor;
class Message;

// 抽象クラス
class FlipperComposite{
public:
	Actor *destination;
	Message *message;

	virtual void autoSend() = 0; //純粋仮想関数

	FlipperComposite(Actor *dest, Message *msg): destination(dest), message(msg){};
	virtual ~FlipperComposite(){}
};

class TickerComposite: FlipperComposite{
public:
	mbed::Ticker *ticker;

	void autoSend();

	TickerComposite(Actor *dest, Message *msg, float periodcTime);
	~TickerComposite();
};

class TimeoutComposite: FlipperComposite{
public:
	mbed::Timeout *timeout;

	void autoSend();

	TimeoutComposite(Actor *dest, Message *msg, float waitTime);
	~TimeoutComposite();
};
#endif /* TICKERCOMPOSIT_H_ */
