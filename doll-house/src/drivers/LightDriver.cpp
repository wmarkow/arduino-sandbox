/*
 * LightDriver.cpp
 *
 *  Created on: 30.08.2017
 *      Author: wmarkow
 */

#include "LightDriver.h"
#include <Arduino.h>

LightDriver::LightDriver(uint8_t pin)
{
    this->pin = pin;
}

void LightDriver::init()
{
    pinMode(pin, OUTPUT);
    switchOff();
}

void LightDriver::switchOn()
{
    digitalWrite(pin, HIGH);
}

void LightDriver::switchOff()
{
    digitalWrite(pin, LOW);
}

bool LightDriver::isOn()
{
    if (digitalRead(pin) == HIGH)
    {
        return true;
    }

    return false;
}

void LightDriver::toggle()
{
    if (isOn())
    {
        switchOff();
    }
    else
    {
        switchOn();
    }
}
