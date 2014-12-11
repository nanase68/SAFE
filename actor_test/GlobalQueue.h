#ifndef ACTOR_TEST_GLOBAL_QUEUE_H_
#define ACTOR_TEST_GLOBAL_QUEUE_H_


// vectorを使えるようにする
#include <vector>

class Message;

static const std::size_t GLOBAL_QUEUE_SIZE = 100;


class GlobalQueue {
private:
	std::vector<Message> vector;

public:
	GlobalQueue();
	Message dequeue();
	void enqueue(Message*);
	bool checkQueue();
};

extern GlobalQueue gqueue;

#endif //ACTOR_TEST_GLOBAL_QUEUE_H_
