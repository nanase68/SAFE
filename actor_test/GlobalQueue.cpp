#include "GlobalQueue.h"

GlobalQueue::GlobalQueue() {
	GlobalQueue::gqueue.clear();
	//GlobalQueue::gqueue().assign(GLOBAL_QUEUE_SIZE, 0);
}

MessagePac GlobalQueue::pop() {
	if (GlobalQueue::gqueue.empty()) {
		// グローバルキューが空
		// ERROR 空キューをpop
		return (0);
	} else {
		MessagePac ret;

		ret = GlobalQueue::gqueue[0];

		return (ret);
	}
}

void GlobalQueue::push(MessagePac m) {
	GlobalQueue::gqueue.push_back(m);
}

bool GlobalQueue::checkQueue() {
	if (GlobalQueue::gqueue.empty()) {
		// グローバルキューが空
		return (false);
	} else {
		GlobalQueue::pop().dealMessagePac();
		return(true);
	}
}
