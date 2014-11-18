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

class Message {
private:
	int content;
	Actor *actor;

public:
	Message operator=(int);
	int get_content(void);
	bool dealMessage(void);

	Message();
	Message(int);
	virtual ~Message();
};

#endif /* MESSAGE_H_ */
