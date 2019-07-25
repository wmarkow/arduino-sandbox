/*
 * BistableOverMonostableSwitch.cpp
 *
 *  Created on: 26.07.2017
 *      Author: wmarkowski
 */

#include "BistableOverMonostableSwitch.h"
#include "Arduino.h"

BistableOverMonostableSwitch::BistableOverMonostableSwitch(uint8_t pin) : MonostableSwitch(pin)
{
	this->state = STATE_OFF;
}

void BistableOverMonostableSwitch::onSwitchOnInternal()
{
	switch(state)
	{
	case STATE_OFF:
		state = STATE_ON;
		this->onSwitchOn();
		break;
	case STATE_ON:
		state = STATE_OFF;
		this->onSwitchOff();
		break;
	}
}

void BistableOverMonostableSwitch::onSwitchOffInternal()
{

}

void BistableOverMonostableSwitch::setStateOn()
{
	state = STATE_ON;
}

void BistableOverMonostableSwitch::setStateOff()
{
	state = STATE_OFF;
}
