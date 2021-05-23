/*
 * CustomDashboard.cpp
 *
 *  Created on: 9 maj 2020
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "CustomDashboard.h"

/***
 * Used to increase the accuracy of the speed from 1 km/h to 0.1 km/h which is being displayed
 * on the stepper gauge, where we can only set speed as uint16_t.
 */
#define SPEED_GAUGE_MULTIPLIER 10

CustomDashboard::CustomDashboard()
{

}

void CustomDashboard::init()
{
   speedGauge.init();
   speedGauge.setValueRange(0, 60 * SPEED_GAUGE_MULTIPLIER);
   speedGauge.reset();

   eepromStorage.read(&eepromData);
   speedSensor.setWheelDiameter(24);
   speedSensor.resetTripDistance(eepromData.totalDistanceInM);
   speedSensorEnabled = true;

   display.init();
}

void CustomDashboard::loop()
{
   speedGauge.loop();

   if (speedSensorEnabled == true)
   {
      float speed = speedSensor.getSpeed();
      float acceleration = speedSensor.getAcceleration();
      speedGauge.setValue(speed * SPEED_GAUGE_MULTIPLIER);

      display.setSpeed(speed);
      display.setAcceleration(acceleration);
      display.setTripDistance(speedSensor.getTripDistance());
      display.setTotalDistance(speedSensor.getTotalDistance());
      if (acceleration < -0.3)
      {
         display.setBreaksOn(true);
      }
      else
      {
         display.setBreaksOn(false);
      }

   }

   if (isInReset())
   {
      display.showLogo();
   }
   else
   {
      display.showDash();
   }
}

void CustomDashboard::reset()
{
   speedGauge.reset();
}

void CustomDashboard::tickSpeedSensor(unsigned long millis)
{
   speedSensor.tick(millis);

   float speed = speedSensor.getSpeed();
   float acceleration = speedSensor.getAcceleration();

   Serial.print(speed);
   Serial.print("   ");
   Serial.println(acceleration);
}

void CustomDashboard::setSpeed(uint8_t speed)
{
   speedSensorEnabled = false;
   speedGauge.setValue(speed * SPEED_GAUGE_MULTIPLIER);

   display.setSpeed(speed);
}

bool CustomDashboard::isInReset()
{
   return speedGauge.isInReset();
}
