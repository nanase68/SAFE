/*
 * Message.h
 *
 *  Created on: 2014/11/17
 *      Author: Ys
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

//前方参照
//#include "Actor.h"
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
