#include "GlobalQueue.h"
#include <stdlib.h>
#include <vector>

#include "Message.h"

GlobalQueue gqueue;

GlobalQueue::GlobalQueue() {
	vector.clear();
	//GlobalQueue::gqueue().assign(GLOBAL_QUEUE_SIZE, 0);
}

Message GlobalQueue::dequeue() {
	if (vector.empty()) {
		// グローバルキューが空
		// ERROR 空キューをpop
		exit(0);
	} else {
		Message ret;

		ret = vector[0];
		vector.erase(vector.begin());

		return (ret);
	}
}

void GlobalQueue::enqueue(Message* m) {
	vector.push_back(*m);
}

bool GlobalQueue::checkQueue() {
	if (vector.empty()) {
		// グローバルキューが空
		return (false);
	} else {
		GlobalQueue::dequeue().dealMessage();
		return(true);
	}
}
