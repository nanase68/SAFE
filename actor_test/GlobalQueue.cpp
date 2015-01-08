#include "GlobalQueue.h"
#include <assert.h>

#include "mbed.h"


GlobalQueue globalPriorityQueue;
GlobalQueue globalNormalQueue;

GlobalQueue::GlobalQueue(size_t maxSize) :
		maxSize(maxSize),
		bufHead((Message **)malloc(sizeof(Message*) * maxSize)),
		bufTail(bufHead + maxSize),
		head(bufHead),
		tail(bufHead),
		size_(0) {

}

GlobalQueue::~GlobalQueue() {
	free(bufHead);
}

Message* GlobalQueue::dequeue() {
	Message *ret;

	__disable_irq();

	if (size_ == 0) {
		ret = NULL;
	} else {
		ret = *head;
		if(++head == bufTail) { head = bufHead; }
		--size_;
	}

	__enable_irq();

	return ret;
}

void GlobalQueue::enqueue(Message* m) {

	__disable_irq();

	if(size_ == maxSize) {
		// buffer overflow
		printf("FATAL: Message Queue Overflow\n");
		exit(1);
	} else {
		*tail = m;
		if(++tail == bufTail) { tail = bufHead; }
		++size_;
	}

	__enable_irq();

	return;
}
