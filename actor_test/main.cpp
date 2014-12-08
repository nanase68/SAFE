#include "mbed.h"

#include "GlobalQueue.h"

Ticker flipper;
DigitalOut led1(LED1);


Actor actor;

void check_queue() {
	MessageInt message(&actor, &actor, 0);
	gqueue.enqueue(&message);
	gqueue.checkQueue();
}

int main() {
	flipper.attach(&check_queue, 2.0); // the address of the function to be attached (flip) and the interval (2 seconds)

}
