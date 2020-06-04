/*
 * CustomDashboard.cpp
 *
 *  Created on: 9 maj 2020
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "CustomDashboard.h"

CustomDashboard::CustomDashboard()
{

}

void CustomDashboard::init()
{
   speedGauge.init();
   speedGauge.setValueRange(0, 60);
   speedGauge.reset();

   speedSensor.setWheelDiameter(24);
   speedSensorEnabled = true;

   display.init();
}

void CustomDashboard::loop()
{
   speedGauge.loop();

   if (speedSensorEnabled == true)
   {
      uint8_t speed = speedSensor.getSpeed();
      speedGauge.setValue(speed);
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
}

void CustomDashboard::setSpeed(uint8_t speed)
{
   speedSensorEnabled = false;
   speedGauge.setValue(speed);
}

bool CustomDashboard::isInReset()
{
   return speedGauge.isInReset();
}
