#include "mbed.h"
#include "Actor.h"
#include "Message.h"
#include "GlobalQueue.h"

DigitalOut led1(LED1);


Actor actor;

void sample1();
void sample2();
void sendWaitSample();
void stateTransTest();

int main() {
	//MessageInt message(&actor, &actor, 0);
	//gqueue.enqueue(&message);

	//actor.start();
	//sample1();
	//sendWaitSample();
	stateTransTest();
	return 0;

}
