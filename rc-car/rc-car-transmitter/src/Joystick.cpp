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
}

uint16_t Joystick::readX()
{
    return analogRead(analogPinX);
}

uint16_t Joystick::readY()
{
    uint16_t y = analogRead(analogPinY);

    return -y + 1023;
}

void Joystick::setReverseY(bool reverseY)
{
    this->reverseY = reverseY;
}
