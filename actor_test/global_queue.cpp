#include <global_queue.h>

GlobalQueue::GlobalQueue() {
	GlobalQueue::gqueue().clear();
	//GlobalQueue::gqueue().assign(GLOBAL_QUEUE_SIZE, 0);
}

MessagePac GlobalQueue::pop() {
	if (GlobalQueue::gqueue().empty()) {
		// ERROR 空スタックをpop
		return (0);
	} else {
		MessagePac ret;

		ret = GlobalQueue::gqueue()[0];

		return (ret);
	}
}

void GlobalQueue::push(MessagePac m) {
	GlobalQueue::gqueue().push_back(m);
}
