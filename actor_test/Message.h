/*
 * Message.h
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Actor.h"
//前方参照（インクルードガードで防がれた時のため）
class Actor;
#include <string>


class Message {
protected:
	Actor *sender, *destination;

public:
	bool dealMessage(void);

	Message();
	Message(Actor*, Actor*);
	virtual ~Message();
};

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

class MessageStr: public Message {
protected:
	std::string content;

public:
	void set_content(std::string);
	Message& operator=(std::string);
	std::string get_content(void);

	MessageStr(Actor*, Actor*, std::string);

	MessageStr();
	virtual ~MessageStr();
};
#endif /* MESSAGE_H_ */
