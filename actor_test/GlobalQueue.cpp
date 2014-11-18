#include "GlobalQueue.h"

GlobalQueue::GlobalQueue() {
	GlobalQueue::gqueue.clear();
	//GlobalQueue::gqueue().assign(GLOBAL_QUEUE_SIZE, 0);
}

Message GlobalQueue::pop() {
	if (GlobalQueue::gqueue.empty()) {
		// グローバルキューが空
		// ERROR 空キューをpop
		return (0);
	} else {
		Message ret;

		ret = GlobalQueue::gqueue[0];

		return (ret);
	}
}

void GlobalQueue::push(Message m) {
	GlobalQueue::gqueue.push_back(m);
}

bool GlobalQueue::checkQueue() {
	if (GlobalQueue::gqueue.empty()) {
		// グローバルキューが空
		return (false);
	} else {
		GlobalQueue::pop().dealMessage();
		return(true);
	}
}
