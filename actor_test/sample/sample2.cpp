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
bool TemperatureActor::receiveMessage(Message *m) {
	if (m->getLabel() == TAM_MODE) {
		displayMode = (DisplayMode) (int) (m->getContent());
		delete m;
	}

	//Try to open the LM75B
	if (sensor.open()) {
		//Print the current temperature
		//printf("Temp = %.3f\n", (float) sensor);

		char* s;
		s = new char[CHAR_SIZE];
		// 前回と同じ値なら更新しない
		if ((pastTemp == (float) sensor) && (m->getLabel() == TAM_CHECK)){
			return false;
		}
		if (displayMode == TEMP_C) {
			sprintf(s, "Temp = %.3f C\n", (float) sensor);
		} else {
			sprintf(s, "Temp = %.3f F\n", ((float) sensor) * 1.8 + 32);
		}
		Message* msgs = new Message(0, s);
		sendTo(&lcdPrintActor, msgs);
		pastTemp = (float) sensor;
	} else {
		error("Device not detected!\n");
	}
	return false;
}
TemperatureActor temperatureActor;

/*
 *
 */
void SendTempF() {
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
class PcInputActor: public Actor {
public:
	bool receiveMessage(Message *m);
};
bool PcInputActor::receiveMessage(Message *m) {
	while (pc.readable()) {
		char c = pc.getc();
		if ((c == 'c') || (c == 'f')) {
			Message* msg;
			if (c == 'c') {
				msg = new Message(TemperatureActor::TAM_MODE,
						(void*) TemperatureActor::TEMP_C);
			} else {
				msg = new Message(TemperatureActor::TAM_MODE,
						(void*) TemperatureActor::TEMP_F);
			}
			sendTo(&temperatureActor, msg);
		}
	}
	return false;
}
PcInputActor pcInputActor;
}	//namespace

/*
 * Main
 */
void sample2() {
	Message m; // 中身の無いメッセージ
	void* v = 0;
	Message msgTemp(TemperatureActor::TAM_CHECK, v);

	sysActor.setPeriodicTask(&temperatureActor, &msgTemp, 1.0);
	sysActor.setPeriodicTask(&pcInputActor, &m, 0.5);
	joystickInterrupt();

	Actor::start();
	return;
}
