/*
 * MessageInt.h
 *
 *  Created on: 2014/12/02
 *      Author: Ys
 */

#ifndef MESSAGEINT_H_
#define MESSAGEINT_H_

#include "Message.h"

class MessageInt: public Message {
protected:
	int content;
public:
	void set_content(int);
	Message& operator=(int);
	int get_content(void);

	MessageInt(Actor*, Actor*, int);
	MessageInt();
	virtual ~MessageInt();
};

#endif /* MESSAGEINT_H_ */
