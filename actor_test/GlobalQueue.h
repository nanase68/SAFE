#ifndef ACTOR_TEST_GLOBAL_QUEUE_H_
#define ACTOR_TEST_GLOBAL_QUEUE_H_

#include <stdlib.h>
class Message;

static const size_t GLOBAL_QUEUE_SIZE = 100;


class GlobalQueue {
private:
	int size;
	Message **bufHead;
	Message **bufTail;
	Message **head;
	Message **tail;

public:
	GlobalQueue(size_t size = GLOBAL_QUEUE_SIZE);
	Message* dequeue();
	void enqueue(Message*);
};

extern GlobalQueue globalPriorityQueue;
extern GlobalQueue globalNormalQueue;

#endif //ACTOR_TEST_GLOBAL_QUEUE_H_
