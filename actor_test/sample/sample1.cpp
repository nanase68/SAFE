/*
 * sample2.cpp
 *
 *  Created on: 2014/12/15
 *      Author: Ys
 */

#include "Actor.h"
#include "Message.h"
#include "SystemActor.h"

#include "mbed.h"
#include "C12832.h"

namespace {

// LED
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// Analog input
AnalogIn pot1(p19);
AnalogIn pot2(p20);

// lcd
C12832 lcd(p5, p7, p6, p8, p11);

// rgb
// rgbの宣言はクラス宣言で行う
const float BRIGHT = 0.9;
const float OFF = 1.0;

// joystick
BusIn joy(p15, p12, p13, p16); // u d l r
DigitalIn fire(p14);

// speaker
PwmOut spkr(p26);
int count = 0;

// Rn42
Serial RN42(p9, p10);
Serial pc(USBTX, USBRX);
DigitalOut RN42_reset_pin(p30);

/*
 * LED2,3,4を順番に光らせる
 */
class MyActor: public Actor {
public:
	bool receiveMessage(Message *m);
};

bool MyActor::receiveMessage(Message *m) {
	if ((led2 == 0) && (led3 == 0) && (led4 == 0)) {
		led2 = 1;
	} else {
		int temp = led4;
		led4 = led3;
		led3 = led2;
		led2 = temp;
	}
	return false;
}

/*
 * LED1をチカチカさせる
 */
class MyActor2: public Actor {
public:
	bool receiveMessage(Message *m);
};

bool MyActor2::receiveMessage(Message *m) {
	led1 = !led1;
	return false;
}

/*
 *
 */
class CheckActor: public Actor {
public:
	bool receiveMessage(Message *m);
};

bool CheckActor::receiveMessage(Message *m) {

	return false;
}

/*
 * アナログ抵抗器の値をディスプレイに表示
 */
class LcdPrintActor: public Actor {
public:
	bool receiveMessage(Message*);

	LcdPrintActor();
};

LcdPrintActor::LcdPrintActor() :
		Actor() {
	lcd.set_auto_up(0);
}

bool LcdPrintActor::receiveMessage(Message *m) {
	int p1 = pot1.read_u16();
	int p2 = pot2.read_u16();

	//if (count <= 50) {
	lcd.locate(0, 0);
	lcd.printf("Pot1 : %04X ", p1);
	p1 = p1 * lcd.width() / 0xffff;
	lcd.fillrect(0, 9, p1, 14, 1);
	lcd.fillrect(p1 + 1, 9, lcd.width() - 1, 14, 0);
	//}

	lcd.locate(0, 16);
	lcd.printf("Pot2 : %04X ", p2);
	p2 = p2 * lcd.width() / 0xffff;
	lcd.fillrect(0, 25, p2, 30, 1);
	lcd.fillrect(p2 + 1, 25, lcd.width(), 30, 0);

	lcd.copy_to_lcd();
	count++;
	return false;
}

/*
 * joystick入力をみてライトを光らせる
 */
class RgbBrightenActor: public Actor {
public:
	bool receiveMessage(Message* m);
	RgbBrightenActor();
	PwmOut r;
	PwmOut g;
	PwmOut b;
};
RgbBrightenActor::RgbBrightenActor() :
		Actor(), r(PwmOut(p23)), g(PwmOut(p24)), b(PwmOut(p25)) {
	// rgb off(r, g, b are off if value is 1)
	r = OFF;
	g = OFF;
	b = OFF;
}
bool RgbBrightenActor::receiveMessage(Message* m) {
	if (joy & 0b1000) {
		r = BRIGHT;
	} else if (joy & 0b0100) {
		g = BRIGHT;
	} else if (joy & 0b0010) {
		b = BRIGHT;
	} else if (joy & 0b0001) {
		r = (1 - (1 - BRIGHT) / 2);
		b = (1 - (1 - BRIGHT) / 2);
	} else if (fire) {
		r = (1 - (1 - BRIGHT) / 3);
		g = (1 - (1 - BRIGHT) / 3);
		b = (1 - (1 - BRIGHT) / 3);
	} else {
		r = OFF;
		g = OFF;
		b = OFF;
	}
	return true;
}

/*
 * joystickのfireを感知して、音を鳴らす
 */
class SpeakerActor: public Actor {
public:
	bool receiveMessage(Message* m);
};
bool SpeakerActor::receiveMessage(Message *m) {
	if (fire) {
		for (float i = 2000.0; i < 10000.0; i += 100) {
			spkr.period(1.0 / i);
			spkr = 0.5;
			wait(0.1);
		}
		spkr = 0.0;
		return true;
	} else {
		return false;
	}
}
/*
 *
 */
class Rn42SlaveActor: public Actor {
public:
	Rn42SlaveActor();
	bool receiveMessage(Message* m);
	short RN42_reset();
};
Rn42SlaveActor::Rn42SlaveActor() {
	RN42.baud(115200);
}
bool Rn42SlaveActor::receiveMessage(Message *m) {
	if (joy != 0b0000) {
		Rn42SlaveActor::RN42_reset();
	}
	while (pc.readable()) {
		RN42.putc(pc.getc());
	}
	while (RN42.readable()) {
		pc.putc(RN42.getc());
	}

	//printf("#");
	return true;
}
short Rn42SlaveActor::RN42_reset(void) {
	char buff[3];
	short i = 0;

	RN42_reset_pin = 0;
	wait_ms(500);
	RN42_reset_pin = 1;
	wait(2);
	pc.printf("checking reset\n");
	RN42.printf("$$$");
	for (i = 0; i < 3; i++) {
		buff[i] = RN42.getc();
	}
	/*
	pc.printf("buffer = %s\n", buff);
	if ((buff[0] == 67) && (buff[1] == 77) && (buff[2] == 68)) { //CMD
		RN42.printf("---\n");
		while (RN42.getc() != 68)
			;
		while (RN42.getc() != 10)
			;
		pc.printf("reset successful\n");
		return 1;
	}

	 */
	RN42.printf("---\n");
	//pc.printf("reset failed...\n");
	return 0;
}
}	//namespace

/*
 * Main
 */
void sample1() {
	MyActor a;
	MyActor2 a2;
	LcdPrintActor a3;
	RgbBrightenActor a4;
	SpeakerActor a5;
	Rn42SlaveActor a6;
	Message m, m2, m3, m4, m5, m6;
	//a2.sendTo(&a2, &m2);
	sysActor.setPeriodicTask(&a, &m, 1.0);
	sysActor.setPeriodicTask(&a2, &m2, 2.0);
	sysActor.setPeriodicTask(&a3, &m3, 0.1);
	sysActor.setPeriodicTask(&a4, &m4, 0.1);
	sysActor.setPeriodicTask(&a5, &m5, 0.1);
	sysActor.setPeriodicTask(&a6, &m6, 0.1);

	printf("Start!!\n");
	Actor::start();
	return;
}
