#include "mbed.h"

#include "GlobalQueue.h"

Ticker flipper;
DigitalOut led1(LED1);
DigitalOut led2(LED2);

GlobalQueue gqueue;

void check_queue() {
	gqueue.checkQueue();
}

int main() {
	flipper.attach(&check_queue, 2.0); // the address of the function to be attached (flip) and the interval (2 seconds)

	// spin in a main loop. flipper will interrupt it to call flip
	while (1) {
		led1 = !led1;
		wait(0.2);
	}
}
