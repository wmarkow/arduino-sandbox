/*
 * SpeedSensor.cpp
 *
 *  Created on: 16 Oct 2019
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "SpeedSensor.h"

#define DEBOUNCE_MILLIS 100L

/***
 * Defines minimum sensible speed in km/h
 */
#define MINIMUM_SENSIBLE_SPEED 1

SpeedSensor::SpeedSensor()
{
   t0 = 0;
   t1 = 0;
   t2 = 0;
   wheelDiameterInInches = 27;
   tickCount = 0;
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
   tickCount ++;
}

void SpeedSensor::setWheelDiameter(uint8_t diameterInInches)
{
   this->wheelDiameterInInches = diameterInInches;
}

/***
 * Gets current speed.
 *
 * @return speed in km/h
 */
float SpeedSensor::getSpeed()
{
   unsigned long delta = t0 - t1;
   unsigned long deltaToLastTick = millis() - t0;

   delta = max(delta, deltaToLastTick);

   float speed = (float) (wheelDiameterInInches * 287.0 / delta);
   if (speed <= MINIMUM_SENSIBLE_SPEED)
   {
      return 0;
   }

   return speed;
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
   if (v0 <= MINIMUM_SENSIBLE_SPEED)
   {
      return 0;
   }

   float v1 = wheelDiameterInInches * 287.0 / deltaT1; // in km/h

   float a = 278.0 * (v0 - v1) / deltaT0; // in m/s2

   return a;
}

/***
 * Gets the trip distance. The trip is reset at every device reset.
 *
 * @return trip distance in km.
 */
float SpeedSensor::getTripDistance()
{
   return (float)((float)tickCount * (float)wheelDiameterInInches / 12547.0);
}
