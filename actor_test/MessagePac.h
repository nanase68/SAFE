#ifndef ACTOR_TEST_MESSAGE_PAC_H_
#define ACTOR_TEST_MESSAGE_PAC_H_

#include "Message.h"
#include "Actor.h"

class MessagePac {
private:
	Message *message;
	Actor *actor;

public:
	MessagePac();
	MessagePac(int i);
	void operator=(int);
	Message *get_message(void);
	bool dealMessagePac(void);

};

#endif //ACTOR_TEST_MESSAGE_PAC_H_
