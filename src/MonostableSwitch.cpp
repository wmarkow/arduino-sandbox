/*
 * MonostableSwitch.cpp
 *
 *  Created on: 25.07.2017
 *      Author: wmarkowski
 */

#include "MonostableSwitch.h"
#include "Arduino.h"

MonostableSwitch::MonostableSwitch(uint8_t pin) : AbstractSwitch(pin)
{
	this->onSwitchOn = NULL;
	this->onSwitchOff = NULL;

	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);
}

void MonostableSwitch::setOnSwitchOn(void (*onSwitchOn)())
{
	this->onSwitchOn = onSwitchOn;
}

void MonostableSwitch::setOnSwitchOff(void (*onSwitchOff)())
{
	this->onSwitchOff = onSwitchOff;
}

void MonostableSwitch::onSwitchOnInternal()
{
	if(this->onSwitchOn != NULL)
	{
		this->onSwitchOn();
	}
}

void MonostableSwitch::onSwitchOffInternal()
{
	if(this->onSwitchOff != NULL)
	{
		this->onSwitchOff();
	}
}
