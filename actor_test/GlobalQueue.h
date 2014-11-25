#ifndef ACTOR_TEST_GLOBAL_QUEUE_H_
#define ACTOR_TEST_GLOBAL_QUEUE_H_

#include "Message.h"

// vectorを使えるようにする
#include <vector>

static const std::size_t GLOBAL_QUEUE_SIZE = 100;

class GlobalQueue {
private:
	std::vector<Message> gqueue;

public:
	GlobalQueue();
	Message dequeue();
	void enqueue(Message);
	bool checkQueue();
};

#endif //ACTOR_TEST_GLOBAL_QUEUE_H_
