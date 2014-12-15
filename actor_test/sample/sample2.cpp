/*
 * sample2.cpp
 *
 *  Created on: 2014/12/15
 *      Author: Ys
 */

#include "mbed.h"
#include "C12832.h"

AnalogIn pot1(p19);
AnalogIn pot2(p20);

C12832 lcd(p5, p7, p6, p8, p11);

int main__()
{
    int p1, p2;

    lcd.set_auto_up(0);

    while(true) {
        p1 = pot1.read_u16();
        p2 = pot2.read_u16();

        lcd.locate(0, 0);
        lcd.printf("Pot1 : %04X ", p1);
        p1 = p1 * lcd.width() / 0xffff;
        lcd.fillrect(0, 9, p1, 14, 1);
        lcd.fillrect(p1 + 1, 9, lcd.width() - 1, 14, 0);
        lcd.locate(0, 16);

        lcd.printf("Pot2 : %04X ", p2);
        p2 = p2 * lcd.width() / 0xffff;
        lcd.fillrect(0, 25, p2, 30, 1);
        lcd.fillrect(p2 + 1, 25, lcd.width(), 30, 0);

        lcd.copy_to_lcd();

        wait(0.1);
    }
}



