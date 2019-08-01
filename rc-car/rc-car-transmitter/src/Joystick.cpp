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
    return analogRead(analogPinX) - 512;
}

int16_t Joystick::readY()
{
    int16_t y = analogRead(analogPinY) - 512;

    if (abs(y) <= zeroValueThreshold)
    {
        y = 0;
    }

    if (reverseY)
    {
        return -y;
    }
    return y;
}

void Joystick::setReverseY(bool reverseY)
{
    this->reverseY = reverseY;
}

void Joystick::setZeroValueThreshold(uint8_t threshold)
{
    this->zeroValueThreshold = threshold;
}
