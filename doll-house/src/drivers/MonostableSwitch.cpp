/*
 * MonostableSwitch.cpp
 *
 *  Created on: 25.07.2017
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "MonostableSwitch.h"

MonostableSwitch::MonostableSwitch(uint8_t pin)
{
    this->pin = pin;
}

void MonostableSwitch::init()
{
    pinMode(pin, INPUT);
    digitalWrite(pin, HIGH);
}

int MonostableSwitch::readButtonState()
{
    return digitalRead(pin);
}
