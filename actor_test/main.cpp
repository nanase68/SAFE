#include "mbed.h"

#include "global_queue.h"

Ticker flipper;
DigitalOut led1(LED1);
DigitalOut led2(LED2);

void check_queue() {
	led2 = !led2;
}

int main() {
	led2 = 1;
	flipper.attach(&check_queue, 2.0); // the address of the function to be attached (flip) and the interval (2 seconds)

	// spin in a main loop. flipper will interrupt it to call flip
	while (1) {
		led1 = !led1;
		wait(0.2);
	}
}
