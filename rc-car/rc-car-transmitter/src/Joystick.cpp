/*
 * Joystick.cpp
 *
 *  Created on: 31 lip 2019
 *      Author: Witold Markowski
 */

#include "Joystick.h"
#include <Arduino.h>

Joystick::Joystick(uint8_t analogPinX, uint8_t analogPinY)
{
    this->analogPinX = analogPinX;
    this->analogPinY = analogPinY;
    this->reverseY = false;
    this->zeroValueThreshold = 0;
}

int16_t Joystick::readX()
{
    int16_t value = analogRead(analogPinX) - 512;

    if (abs(value) <= zeroValueThreshold)
    {
        value = 0;
    }

    return value;
}

int16_t Joystick::readY()
{
    int16_t value = analogRead(analogPinY) - 512;

    if (abs(value) <= zeroValueThreshold)
    {
        value = 0;
    }

    if (reverseY)
    {
        return -value;
    }
    return value;
}

void Joystick::setReverseY(bool reverseY)
{
    this->reverseY = reverseY;
}

void Joystick::setZeroValueThreshold(uint8_t threshold)
{
    this->zeroValueThreshold = threshold;
}
