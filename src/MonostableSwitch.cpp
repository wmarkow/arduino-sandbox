/*
 * MonostableSwitch.cpp
 *
 *  Created on: 25.07.2017
 *      Author: wmarkowski
 */

#include "MonostableSwitch.h"
#include "Arduino.h"

MonostableSwitch::MonostableSwitch(uint8_t pin)
{
	this->firstTimestamp = 0;
	this->pin = pin;
	this->state = STATE_OFF;
	this->onSwitchOn = NULL;
	this->onSwitchOff = NULL;

	pinMode(pin, INPUT);
	digitalWrite(pin, HIGH);
}

void MonostableSwitch::loop()
{
	int readPin = digitalRead(pin);

	switch(state)
	{
	case STATE_OFF:
		if(readPin == LOW)
		{
			state = STATE_FIRST_ON;
			firstTimestamp = millis();
		}
		break;
	case STATE_FIRST_ON:
		if(millis() - firstTimestamp < 100)
		{
			break;
		}
		if(readPin == LOW)
		{
			// STATE_ON detected
			state = STATE_ON;
			if(this->onSwitchOn != NULL)
			{
				this->onSwitchOn();
			}
		} else
		{
			state = STATE_OFF;
		}
		break;
	case STATE_ON:
		if(readPin == HIGH)
		{
			state = STATE_FIRST_OFF;
			firstTimestamp = millis();
		}
		break;
	case STATE_FIRST_OFF:
		if(millis() - firstTimestamp < 100)
		{
			break;
		}
		if(readPin == LOW)
		{
			state = STATE_ON;
		} else
		{
			// STATE_OFF detected
			state = STATE_OFF;
			if(this->onSwitchOff != NULL)
			{
				this->onSwitchOff();
			}
		}
		break;
	}
}

void MonostableSwitch::setOnSwitchOn(void (*onSwitchOn)())
{
	this->onSwitchOn = onSwitchOn;
}

void MonostableSwitch::setOnSwitchOff(void (*onSwitchOff)())
{
	this->onSwitchOff = onSwitchOff;
}
