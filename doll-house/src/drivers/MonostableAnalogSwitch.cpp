/*
 * MonostableAnalogSwitch.cpp
 *
 *  Created on: 2 gru 2019
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "MonostableAnalogSwitch.h"

MonostableAnalogSwitch::MonostableAnalogSwitch(uint8_t pin, uint16_t minValue,
        uint16_t maxValue) :
        MonostableSwitch(pin)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
}

void MonostableAnalogSwitch::init()
{
    pinMode(pin, INPUT);
}

int MonostableAnalogSwitch::readButtonState()
{
    uint16_t adcRead = analogRead(pin);

    if (adcRead >= minValue && adcRead <= maxValue)
    {
        return LOW;
    }

    return HIGH;
}
