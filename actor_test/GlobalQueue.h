#ifndef ACTOR_TEST_GLOBAL_QUEUE_H_
#define ACTOR_TEST_GLOBAL_QUEUE_H_

#include "MessagePac.h"

// vectorを使えるようにする
#include <vector>

static const std::size_t GLOBAL_QUEUE_SIZE = 100;

class GlobalQueue {
private:
	std::vector<MessagePac> gqueue;

public:
	GlobalQueue();
	MessagePac pop();
	void push(MessagePac);
	bool checkQueue();
};

#endif //ACTOR_TEST_GLOBAL_QUEUE_H_
