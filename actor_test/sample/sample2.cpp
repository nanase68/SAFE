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

#define CHAR_SIZE 64
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

// Rn42
Serial RN42(p9, p10);
Serial pc(USBTX, USBRX);
DigitalOut RN42_reset_pin(p30);

// LM75B
//Create an LM75B object at the default address (ADDRESS_0)
LM75B sensor(p28, p27);

/*
 *
 */
class MyActor: public Actor {
public:
	bool receiveMessage(Message *m);
};
bool MyActor::receiveMessage(Message *m) {
	return false;
}

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
	char* s = (char*)m->getContent();
	lcd.locate(0, label2locate(m->getLabel()));
	lcd.printf("%s ", s);

	lcd.copy_to_lcd();
	delete (char*)m->getContent();
	delete m;
	return false;
}
int LcdPrintActor::label2locate(int i){
	if(i == 0){
		return 0;
	}else{
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
	bool receiveMessage(Message *m);
	TemperatureActor();
};
TemperatureActor::TemperatureActor(){
	printf("TemperatureActor start!!\n");
}
bool TemperatureActor::receiveMessage(Message *m) {
	//Try to open the LM75B
	if (sensor.open()) {
		//Print the current temperature
		//printf("Temp = %.3f\n", (float) sensor);

		char* s;
		s = new char[CHAR_SIZE];
		if(pastTemp == (float) sensor){
			return true;
		}
		sprintf(s, "Temp = %.3f\n", (float) sensor);
		Message* msgs = new Message(0, s);
		sendTo(&lcdPrintActor, msgs);
		pastTemp = (float) sensor;
		return true;
	} else {
		error("Device not detected!\n");
		return false;
	}
}
TemperatureActor temperatureActor;
}	//namespace

/*
 * Main
 */
void sample2() {
	MyActor a;
	Message m, m2;

	sysActor.setPeriodicTask(&temperatureActor, &m2, 1.0);

	Actor::start();
	return;
}
