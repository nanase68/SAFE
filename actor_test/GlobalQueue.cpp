#include "GlobalQueue.h"
#include <assert.h>

#include "mbed.h"


GlobalQueue globalPriorityQueue;
GlobalQueue globalNormalQueue;

GlobalQueue::GlobalQueue(size_t size) :
		size(size),
		bufHead((Message **)malloc(sizeof(Message*) * size)),
		bufTail(bufHead + size),
		head(NULL),
		tail(NULL) {

}

Message* GlobalQueue::dequeue() {
	Message *ret;

	__disable_irq();

	if (head == NULL) {
		assert(tail == NULL);
		ret = NULL;
	} else {
		assert(tail != NULL);
		ret = *head;
		if(head == tail) {
			head = tail = NULL;
		} else {
			++head;
			if(head == bufTail) { head = bufHead; }
		}

	}

	__enable_irq();

	return ret;
}

void GlobalQueue::enqueue(Message* m) {

	__disable_irq();

	if(head == NULL) {
		assert(tail == NULL);
		head = tail = bufHead;
	} else {
		assert(tail != NULL);
		++tail;
		if(tail == bufTail) { tail = bufHead; };
		if(tail == head) {
			// buffer overflow
			printf("FATAL: Message Queue Overflow\n");
			exit(1);
		}

	}

	*tail = m;

	__enable_irq();

	return;
}
