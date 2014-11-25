#include "mbed.h"

#include "GlobalQueue.h"

Ticker flipper;
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

GlobalQueue gqueue;
Actor actor;

void check_queue() {
	Message message(&actor);
	gqueue.enqueue(message);
	gqueue.checkQueue();
}

int main() {
	flipper.attach(&check_queue, 2.0); // the address of the function to be attached (flip) and the interval (2 seconds)

	// spin in a main loop. flipper will interrupt it to call flip
	while (1) {
		led1 = !led1;
		wait(0.2);

		int temp = led4;
		led4 = led3;
		led3 = led2;
		led2 = temp;
	}
}
