
#ifndef ACTOR_TEST_GLOBAL_QUEUE_H_
#define ACTOR_TEST_GLOBAL_QUEUE_H_

#include "message_pac.h"

// vectorを使えるようにする
#include <vector>

static const std::size_t GLOBAL_QUEUE_SIZE = 100;

class GlobalQueue{
private:
    std::vector<GlobalQueue> gqueue();

public:
    GlobalQueue();
	MessagePac pop();
	void push(MessagePac);
};


#endif //ACTOR_TEST_GLOBAL_QUEUE_H_
