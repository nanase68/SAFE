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

namespace {

/*
 * 関数プロトタイプ宣言
 */
class LcdPrintActor: public Actor {
private:
	// lcd
	C12832 lcd;
public:
	bool receiveMessage(Message*);
	int label2locate(int i);

	LcdPrintActor();
};
LcdPrintActor lcdPrintActor;
class TemperatureActor: public Actor {
private:
// LM75B
	LM75B sensor;
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
	TemperatureActor() :
			sensor(p28, p27) {
	}
	;
};
TemperatureActor temperatureActor;

class PcInputControlActor: public Actor {
public:
	bool receiveMessage(Message *m);
};
PcInputControlActor pcInputControlActor;

class PcInputCatchActor: public Actor {
private:
	// シリアル通信
	Serial pc;
public:
	bool receiveMessage(Message *m);
	PcInputCatchActor() :
			pc(USBTX, USBRX) {
	}
	;
};
PcInputCatchActor pcInputCatchActor;

/*
 *
 */
LcdPrintActor::LcdPrintActor() :
		Actor(), lcd(p5, p7, p6, p8, p11) {
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

/*
 *
 */
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
	}

	return false;
}

/*
 *
 */
void joystickInterrupt() {
	// joystick
	const PinName &joy_u = p15;
	const PinName &joy_d = p12;
	const PinName &joy_l = p13;
	const PinName &joy_r = p16;
	const PinName &joy_c = p14;

	InputActor JoyStickInterrupt;
	Message *msg_f = new Message(TemperatureActor::TAM_MODE, (void*) TemperatureActor::TEMP_F);
	Message *msg_c = new Message(TemperatureActor::TAM_MODE, (void*) TemperatureActor::TEMP_C);

	JoyStickInterrupt.setInterrput(&temperatureActor, msg_c, joy_u);
	JoyStickInterrupt.rise();
	JoyStickInterrupt.setInterrput(&temperatureActor, msg_c, joy_d);
	JoyStickInterrupt.rise();
	JoyStickInterrupt.setInterrput(&temperatureActor, msg_c, joy_l);
	JoyStickInterrupt.rise();
	JoyStickInterrupt.setInterrput(&temperatureActor, msg_c, joy_r);
	JoyStickInterrupt.rise();
	JoyStickInterrupt.setInterrput(&temperatureActor, msg_f, joy_c);
	JoyStickInterrupt.rise();
}

/*
 *
 */
Message msg_f_serial(TemperatureActor::TAM_MODE,
		(void*) TemperatureActor::TEMP_F);
Message msg_c_serial(TemperatureActor::TAM_MODE,
		(void*) TemperatureActor::TEMP_C);
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
		m = &msg_f_serial;
	} else {
		m = &msg_c_serial;
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
 * Actor::startは処理が戻ってこないのでここでスタックに置いたものは破棄されない
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
