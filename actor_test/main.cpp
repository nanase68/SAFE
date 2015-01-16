#include "mbed.h"
#include "Actor.h"
#include "Message.h"
#include "GlobalQueue.h"

DigitalOut led1(LED1);


Actor actor;

void sample1();
void sample2();
void sendWaitSample();

int main() {
	//MessageInt message(&actor, &actor, 0);
	//gqueue.enqueue(&message);

	//actor.start();
	sample2();
	//sendWaitSample();
	return 0;

}
