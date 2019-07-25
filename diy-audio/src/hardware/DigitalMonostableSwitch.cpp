/*
 * DigitalMonostableSwitch.cpp
 *
 *  Created on: 03.11.2017
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "DigitalMonostableSwitch.h"

DigitalMonostableSwitch::DigitalMonostableSwitch(uint8_t pin) :
      MonostableSwitch(pin)
{

}

int DigitalMonostableSwitch::readButtonState()
{
   return digitalRead(pin);
}

