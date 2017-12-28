/*
 * AnalogMonostableSwitch.cpp
 *
 *  Created on: 03.11.2017
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "AnalogMonostableSwitch.h"

AnalogMonostableSwitch::AnalogMonostableSwitch(uint8_t pin, uint16_t minValue,
      uint16_t maxValue) :
      MonostableSwitch(pin)
{
   this->minValue = minValue;
   this->maxValue = maxValue;
}

int AnalogMonostableSwitch::readButtonState()
{
   uint16_t adcRead = analogRead(0);

   if (adcRead >= minValue && adcRead <= maxValue)
   {
      return LOW;
   }

   return HIGH;
}

