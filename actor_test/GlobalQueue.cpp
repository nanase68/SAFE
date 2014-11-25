#include "GlobalQueue.h"

GlobalQueue::GlobalQueue() {
	GlobalQueue::gqueue.clear();
	//GlobalQueue::gqueue().assign(GLOBAL_QUEUE_SIZE, 0);
}

Message GlobalQueue::dequeue() {
	if (GlobalQueue::gqueue.empty()) {
		// グローバルキューが空
		// ERROR 空キューをpop
		return (0);
	} else {
		Message ret;

		ret = GlobalQueue::gqueue[0];
		GlobalQueue::gqueue.erase(GlobalQueue::gqueue.begin());

		return (ret);
	}
}

void GlobalQueue::enqueue(Message m) {
	GlobalQueue::gqueue.push_back(m);
}

bool GlobalQueue::checkQueue() {
	if (GlobalQueue::gqueue.empty()) {
		// グローバルキューが空
		return (false);
	} else {
		GlobalQueue::dequeue().dealMessage();
		return(true);
	}
}
