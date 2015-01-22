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
#include "LM75B/LM75B.h"

#define CHAR_SIZE 16
// MEMO: ここの値が大きすぎるとLcdPrintActor::receiveMessageが呼ばれないバグ
//　　　　　現在の時点でも長く起動すると↑のバグが発生
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
//BusIn joy(p15, p12, p13, p16); // u d l r
//DigitalIn fire(p14);
InterruptIn joy_u(p15);
InterruptIn joy_d(p12);
InterruptIn joy_l(p13);
InterruptIn joy_r(p16);
InterruptIn joy_c(p14);

// speaker
PwmOut spkr(p26);

// シリアル通信
Serial pc(USBTX, USBRX);

// LM75B
//Create an LM75B object at the default address (ADDRESS_0)
LM75B sensor(p28, p27);

/*
 * 関数プロトタイプ宣言
 */
class PcInputControlActor: public Actor {
public:
	bool receiveMessage(Message *m);
};
PcInputControlActor pcInputControlActor;

class PcInputCatchActor: public Actor {
public:
	bool receiveMessage(Message *m);
};
PcInputCatchActor pcInputCatchActor;
/*
 *
 */
class LcdPrintActor: public Actor {
public:
	bool receiveMessage(Message*);
	int label2locate(int i);

	LcdPrintActor();
};
LcdPrintActor::LcdPrintActor() :
		Actor() {
	lcd.set_auto_up(0);
}
bool LcdPrintActor::receiveMessage(Message *m) {
	char* s = (char*) m->getContent();
	lcd.locate(0, label2locate(m->getLabel()));
	lcd.printf("%s ", s);

	lcd.copy_to_lcd();
	delete (char*) m->getContent();
	delete m;
	return false;
}
int LcdPrintActor::label2locate(int i) {
	if (i == 0) {
		return 0;
	} else {
		puts("invalid labed : LcdPrintActor");
		return 0;
	}
}
LcdPrintActor lcdPrintActor;

/*
 *
 */
class TemperatureActor: public Actor {
private:
	float pastTemp;
	bool checkSensor(Message *m);
public:
	enum Mode {
		TAM_CHECK, TAM_MODE,
	};
	enum DisplayMode {
		TEMP_C, TEMP_F,
	} displayMode;
	bool receiveMessage(Message *m);
	TemperatureActor();
};
TemperatureActor::TemperatureActor() {
	printf("TemperatureActor start!!\n");
}
bool TemperatureActor::checkSensor(Message *m) {
	//Try to open the LM75B
	if (sensor.open()) {
		// 前回と同じ値なら更新しない
		if ((pastTemp == (float) sensor) && (m->getLabel() == TAM_CHECK)) {
			return true;
		}

		char* s;
		s = new char[CHAR_SIZE];
		if (displayMode == TEMP_C) {
			sprintf(s, "Temp = %.3f C\n", (float) sensor);
		} else {
			sprintf(s, "Temp = %.3f F\n", ((float) sensor) * 1.8 + 32);
		}
		Message* msgs = new Message(0, s);
		sendTo(&lcdPrintActor, msgs);
		pastTemp = (float) sensor;
		return true;
	} else {
		error("Device not detected!\n");
		return false;
	}
}
bool TemperatureActor::receiveMessage(Message *m) {
	if (m->getLabel() == TAM_CHECK) {
		checkSensor(m);
	} else if (m->getLabel() == TAM_MODE) {
		displayMode = (DisplayMode) (int) (m->getContent());
		checkSensor(m);
		delete m;
	}

	return false;
}
TemperatureActor temperatureActor;

/*
 *
 */
void SendTempF() {
	// FIX:ここでnewしたらやばい
	Message* msg = new Message(TemperatureActor::TAM_MODE,
			(void*) TemperatureActor::TEMP_F);
	sysActor.sendTo(&temperatureActor, msg);
}
void SendTempC() {
	Message* msg = new Message(TemperatureActor::TAM_MODE,
			(void*) TemperatureActor::TEMP_C);
	sysActor.sendTo(&temperatureActor, msg);
}
void joystickInterrupt() {
	joy_u.rise(&SendTempC);
	joy_d.rise(&SendTempC);
	joy_l.rise(&SendTempC);
	joy_r.rise(&SendTempC);
	joy_c.rise(&SendTempF);
}

/*
 *
 */
bool PcInputControlActor::receiveMessage(Message *m) {
	char c;
	Message msg;

	c = (char) (int) m->getContent();
	delete m;
	if (c != 't') {
		return false;
	}
	m = sendWait(&pcInputCatchActor, &msg);

	c = (char) (int) m->getContent();
	delete m;
	if (c != 'e') {
		return false;
	}
	m = sendWait(&pcInputCatchActor, &msg);

	c = (char) (int) m->getContent();
	delete m;
	if (c != 'm') {
		return false;
	}
	m = sendWait(&pcInputCatchActor, &msg);

	c = (char) (int) m->getContent();
	delete m;
	if (c != 'p') {
		return false;
	}
	m = sendWait(&pcInputCatchActor, &msg);

	c = (char) (int) m->getContent();
	delete m;
	if ((c != 'f') && (c != 'c')) {
		return false;
	}
	if (c == 'f') {
		m = new Message(TemperatureActor::TAM_MODE,
				(void*) TemperatureActor::TEMP_F);
	} else {
		m = new Message(TemperatureActor::TAM_MODE,
				(void*) TemperatureActor::TEMP_C);

	}
	sendTo(&temperatureActor, m);

	return true;
}

/*
 *
 */
bool PcInputCatchActor::receiveMessage(Message *m) {
	while (pc.readable()) {
		int i = pc.getc();
		Message* msg = new Message(0, (void*) i);
		sendTo(&pcInputControlActor, msg);
	}
	return false;
}
}	//namespace

/*
 * Main
 */
void sample2() {
	Message m; // 中身の無いメッセージ
	void* v = 0;
	Message msgTemp(TemperatureActor::TAM_CHECK, v);

	sysActor.setPeriodicTask(&temperatureActor, &msgTemp, 1.0);
	sysActor.setPeriodicTask(&pcInputCatchActor, &m, 0.5);
	joystickInterrupt();

	Actor::start();
	return;
}
