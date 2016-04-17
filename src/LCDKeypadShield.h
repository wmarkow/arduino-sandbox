/*
 * LCDKeypadShield.h
 *
 *  Created on: 17 kwi 2016
 *      Author: witek
 */

#ifndef LCDKEYPADSHIELD_H_
#define LCDKEYPADSHIELD_H_

#include <LiquidCrystal.h>
#include <Arduino.h>

enum LCDKeypadShieldButton
{
	BUTTON_RIGHT = 0,
	BUTTON_UP = 1,
	BUTTON_DOWN = 2,
	BUTTON_LEFT = 3,
	BUTTON_SELECT = 4,
	BUTTON_NONE   = 5
};

class LCDKeypadShield : public LiquidCrystal
{
public:
	LCDKeypadShield(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
	LCDKeypadShieldButton getButton();
};



#endif /* LCDKEYPADSHIELD_H_ */
