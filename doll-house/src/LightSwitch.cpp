/*
 * LightSwitch.cpp
 *
 *  Created on: 04.09.2017
 *      Author: wmarkowski
 */

#include "LightSwitch.h"

LightSwitch::LightSwitch(uint8_t switch_pin, uint8_t light_pin) : BistableOverMonostableSwitch(switch_pin), lightDriver(light_pin)
{

}

void LightSwitch::init()
{
	BistableOverMonostableSwitch::init();
	lightDriver.init();
}

void LightSwitch::switchOn()
{
	setStateOn();
	onSwitchOn();
}
void LightSwitch::switchOff()
{
	setStateOff();
	onSwitchOff();
}

void LightSwitch::onSwitchOn()
{
	lightDriver.switchOn();
}

void LightSwitch::onSwitchOff()
{
	lightDriver.switchOff();
}
