#include "GlobalQueue.h"
#include <stdlib.h>
#include <vector>

#include "Message.h"

GlobalQueue globalPriorityQueue;
GlobalQueue globalNormalQueue;

GlobalQueue::GlobalQueue() {
	messageQueue.clear();
	//GlobalQueue::gqueue().assign(GLOBAL_QUEUE_SIZE, 0);
}

Message* GlobalQueue::dequeue() {
	if (messageQueue.empty()) {
		return NULL;
	} else {
		Message ret;

		ret = messageQueue[0];
		messageQueue.erase(messageQueue.begin());

		return &ret;
	}
}

void GlobalQueue::enqueue(Message* m) {
	messageQueue.push_back(*m);
}

