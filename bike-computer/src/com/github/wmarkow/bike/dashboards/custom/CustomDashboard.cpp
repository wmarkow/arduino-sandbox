/*
 * CustomDashboard.cpp
 *
 *  Created on: 9 maj 2020
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "CustomDashboard.h"

void CustomDashboard::init()
{
   speedGauge.init();
   speedGauge.setValueRange(0, 60);
   speedGauge.reset();

   speedSensor.setWheelDiameter(24);
   speedSensorEnabled = true;
}

void CustomDashboard::loop()
{
   speedGauge.loop();

   if (speedSensorEnabled == true)
   {
      uint8_t speed = speedSensor.getSpeed();
      speedGauge.setValue(speed);
   }
}

void CustomDashboard::reset()
{
   speedGauge.reset();
}

void CustomDashboard::tickSpeedSensor(unsigned long millis)
{
   speedSensor.tick(millis);
}

void CustomDashboard::setSpeed(uint8_t speed)
{
   speedSensorEnabled = false;
   speedGauge.setValue(speed);
}
