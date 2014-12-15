/*
 * sample2.cpp
 *
 *  Created on: 2014/12/15
 *      Author: Ys
 */

#include <iostream>

#include "Actor.h"
#include "Message.h"
#include "SystemActor.h"

#include "mbed.h"
#include "C12832.h"

namespace {

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

AnalogIn pot1(p19);
AnalogIn pot2(p20);

C12832 lcd(p5, p7, p6, p8, p11);

int count = 0;

class MyActor: public Actor {
public:
	bool receiveMessage(Message *m);
};

bool MyActor::receiveMessage(Message *m) {
	cout << "receiveMessage" << endl;

	if ((led2 == 0) && (led3 == 0) && (led4 == 0)) {
		led2 = 1;
	} else {
		int temp = led4;
		led4 = led3;
		led3 = led2;
		led2 = temp;
	}

	//同じメッセージ使い回し（手抜き）
	//sendTo(this, m);

	return false;
}

class MyActor2: public Actor {
public:
	bool receiveMessage(Message *m);
};

bool MyActor2::receiveMessage(Message *m) {
	cout << "receiveMessage2" << endl;

	led1 = !led1;

	//this->sendTo(this, m);

	return false;
}

class CheckActor: public Actor {
public:
	bool receiveMessage(Message *m);
};

bool CheckActor::receiveMessage(Message *m) {

	return false;
}

class LcdPrintActor: public Actor {
public:
	bool receiveMessage(Message*);

	LcdPrintActor();
};

LcdPrintActor::LcdPrintActor() : Actor(){
	lcd.set_auto_up(0);
}

bool LcdPrintActor::receiveMessage(Message *m) {
	int p1 = pot1.read_u16();
	int p2 = pot2.read_u16();

	if (count <= 50) {
		lcd.locate(0, 0);
		lcd.printf("Pot1 : %04X ", p1);
		p1 = p1 * lcd.width() / 0xffff;
		lcd.fillrect(0, 9, p1, 14, 1);
		lcd.fillrect(p1 + 1, 9, lcd.width() - 1, 14, 0);
	}

	lcd.locate(0, 16);
	lcd.printf("Pot2 : %04X ", p2);
	p2 = p2 * lcd.width() / 0xffff;
	lcd.fillrect(0, 25, p2, 30, 1);
	lcd.fillrect(p2 + 1, 25, lcd.width(), 30, 0);

	lcd.copy_to_lcd();
	count++;
	return false;
}

}	//namespace

void sample1() {
	MyActor a;
	MyActor2 a2;
	LcdPrintActor a3;
	Message m, m2, m3;
	//a2.sendTo(&a2, &m2);
	sysActor.setPeriodicTask(&a, &m, 1.0);
	sysActor.setPeriodicTask(&a2, &m2, 2.0);
	sysActor.setPeriodicTask(&a3, &m3, 0.1);

	cout << "Start!!" << endl;
	Actor::start();
	return;
}
