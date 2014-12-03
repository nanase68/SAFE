/*
 * MessageStr.h
 *
 *  Created on: 2014/12/02
 *      Author: Ys
 */

#ifndef MESSAGESTR_H_
#define MESSAGESTR_H_

#include <string>
#include "Message.h"

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

#endif /* MESSAGESTR_H_ */
