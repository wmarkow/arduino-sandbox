/*
 * SpeedSensor.cpp
 *
 *  Created on: 16 Oct 2019
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "SpeedSensor.h"

#define DEBOUNCE_MILLIS 100L

SpeedSensor::SpeedSensor()
{
    tickInMillis = 0;
    previousTickInMillis = 0;
    wheelDiameterInInches = 27;
}

void SpeedSensor::tick(unsigned long currentMillis)
{
    unsigned long delta = currentMillis - tickInMillis;
    if (delta < DEBOUNCE_MILLIS)
    {
        return;
    }

    previousTickInMillis = tickInMillis;
    tickInMillis = currentMillis;
}

void SpeedSensor::setWheelDiamieter(uint8_t diameterInInches)
{
    this->wheelDiameterInInches = diameterInInches;
}

uint8_t SpeedSensor::getSpeed()
{
    unsigned long delta = tickInMillis - previousTickInMillis;
    unsigned long deltaToLastTick = millis() - tickInMillis;

    delta = max(delta, deltaToLastTick);

    return (uint8_t) (wheelDiameterInInches * 287.0 / delta);
}
