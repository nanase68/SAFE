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

Message GlobalQueue::dequeue() {
	if (messageQueue.empty()) {
		// グローバルキューが空
		// ERROR 空キューをpop
		exit(0);
	} else {
		Message ret;

		ret = messageQueue[0];
		messageQueue.erase(messageQueue.begin());

		return (ret);
	}
}

void GlobalQueue::enqueue(Message* m) {
	messageQueue.push_back(*m);
}

bool GlobalQueue::checkQueue() {
	if (messageQueue.empty()) {
		// グローバルキューが空
		return (false);
	} else {
		GlobalQueue::dequeue().dealMessage();
		return(true);
	}
}
