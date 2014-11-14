
#ifndef ACTOR_TEST_GLOBAL_QUEUE_H_
#define ACTOR_TEST_GLOBAL_QUEUE_H_

#include "message_pac.h"

#define GLOBAL_QUEUE_SIZE 100

class GlobalQueue{
private:
	MessagePac gqueue[GLOBAL_QUEUE_SIZE];

public:
	void init();
	MessagePac pop();
	MessagePac push();
};

#endif //ACTOR_TEST_GLOBAL_QUEUE_H_
