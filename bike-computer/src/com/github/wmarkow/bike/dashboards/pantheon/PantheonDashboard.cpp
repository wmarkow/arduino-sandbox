/*
 * PantheonDashboard.cpp
 *
 *  Created on: 9 maj 2020
 *      Author: wmarkowski
 */

#include "PantheonDashboard.h"

const uint8_t FIRST_MLS10407_CS = 5;
const uint8_t SECOND_MLS10407_CS = 4;

PantheonDashboard::PantheonDashboard() :
      gauge1(FIRST_MLS10407_CS), gauge2(SECOND_MLS10407_CS), tempGauge(&gauge1,
            1), speedGauge(&gauge1, 2), fuelGauge(&gauge2, 1)
{

}

void PantheonDashboard::init()
{
   gauge1.init();
   gauge2.init();

   speedGauge.setAngleRange(3, 260);
   speedGauge.setValueRange(0, 100); // in mph

   // angle 0 points to hour 9
   // angle 90 points to hour 12
   // angle -90 points to hour 6
   tempGauge.setAngleRange(-60, 25);
   tempGauge.setValueRange(0, 100);

   // angle 0 points to hour 3
   // angle 90 points to hour 12
   // angle -90 points to hour 6
   fuelGauge.setAngleRange(-60, 25);
   fuelGauge.setValueRange(0, 100);

   backlight.init();

   speedSensor.setWheelDiameter(24);
}

void PantheonDashboard::loop()
{
   speedGauge.loop();

   uint8_t speed = speedSensor.getSpeed();
   speedGauge.setValue(speed);
}

void PantheonDashboard::tickSpeedSensor(unsigned long millis)
{
   speedSensor.tick(millis);
}

