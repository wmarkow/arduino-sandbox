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
   speedGauge.setValueRange(0, 100);
   speedGauge.reset();

   speedSensor.setWheelDiamieter(24);
}

void CustomDashboard::loop()
{
   speedGauge.loop();

   uint8_t speed = speedSensor.getSpeed();
   speedGauge.setValue(speed);
}

void CustomDashboard::tickSpeedSensor(unsigned long millis)
{
   speedSensor.tick(millis);
}
