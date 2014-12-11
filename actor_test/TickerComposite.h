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
}
class Actor;
class Message;

class TickerComposite{
public:
	mbed::Ticker *ticker;
	Actor *destination;
	Message *message;

	void autoSend();

	TickerComposite(Actor *dest, Message *msg, float periodcTime);
	~TickerComposite();
};

#endif /* TICKERCOMPOSIT_H_ */
