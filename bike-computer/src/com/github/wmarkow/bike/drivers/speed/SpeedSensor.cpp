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
    t2 = 0;
    wheelDiameterInInches = 27;
}

void SpeedSensor::tick(unsigned long currentMillis)
{
    unsigned long delta = currentMillis - t0;
    if (delta < DEBOUNCE_MILLIS)
    {
        return;
    }

    t2 = t1;
    t1 = t0;
    t0 = currentMillis;
}

void SpeedSensor::setWheelDiamieter(uint8_t diameterInInches)
{
    this->wheelDiameterInInches = diameterInInches;
}

/***
 * Gets current speed.
 *
 * @return speed in km/h
 */
uint8_t SpeedSensor::getSpeed()
{
    unsigned long delta = t0 - t1;
    unsigned long deltaToLastTick = millis() - t0;

    delta = max(delta, deltaToLastTick);

    return (uint8_t) (wheelDiameterInInches * 287.0 / delta);
}

/***
 * Gets current acceleration.
 *
 * @return acceleration in m/s2
 *         negative - vehicle slows down
 *         positive - vehicle speeds up
 */
float SpeedSensor::getAcceleration()
{
    unsigned long deltaT0 = max(t0 - t1, millis() - t0); // in ms
    unsigned long deltaT1 = t1 - t2; // in ms

    float v0 = wheelDiameterInInches * 287.0 / deltaT0; // in km/h
    float v1 = wheelDiameterInInches * 287.0 / deltaT1; // in km/h

    float a = 278.0 * (v0 - v1) / deltaT0; // in m/s2

    return a;
}
