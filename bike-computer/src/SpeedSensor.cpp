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
    t0 = 0;
    t1 = 0;
    wheelDiameterInInches = 27;
}

void SpeedSensor::tick(unsigned long currentMillis)
{
    unsigned long delta = currentMillis - t0;
    if (delta < DEBOUNCE_MILLIS)
    {
        return;
    }

    t1 = t0;
    t0 = currentMillis;
}

void SpeedSensor::setWheelDiamieter(uint8_t diameterInInches)
{
    this->wheelDiameterInInches = diameterInInches;
}

uint8_t SpeedSensor::getSpeed()
{
    unsigned long delta = t0 - t1;
    unsigned long deltaToLastTick = millis() - t0;

    delta = max(delta, deltaToLastTick);

    return (uint8_t) (wheelDiameterInInches * 287.0 / delta);
}
