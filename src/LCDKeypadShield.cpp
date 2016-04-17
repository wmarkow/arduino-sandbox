/*
 * LCDKeypadShield.cpp
 *
 *  Created on: 17 kwi 2016
 *      Author: witek
 */

#include "LCDKeypadShield.h"

LCDKeypadShield::LCDKeypadShield(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) : LiquidCrystal(rs, enable,
		d0, d1, d2, d3)
{

}


LCDKeypadShieldButton LCDKeypadShield::getButton()
{
	uint16_t adc_key_in = analogRead(0);

	if (adc_key_in > 1000) return BUTTON_NONE;
	if (adc_key_in < 50)   return BUTTON_RIGHT;
	if (adc_key_in < 250)  return BUTTON_UP;
	if (adc_key_in < 450)  return BUTTON_DOWN;
	if (adc_key_in < 650)  return BUTTON_LEFT;
	if (adc_key_in < 850)  return BUTTON_SELECT;

	return BUTTON_NONE;
}
