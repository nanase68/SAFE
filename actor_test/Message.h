/*
 * Message.h
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

class Message {
private:
	int content;
public:
	void operator=(int);

	Message();
	virtual ~Message();
};

#endif /* MESSAGE_H_ */
