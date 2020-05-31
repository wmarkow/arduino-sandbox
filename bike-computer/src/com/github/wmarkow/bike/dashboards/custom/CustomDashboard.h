/*
 * CustomDashboard.h
 *
 *  Created on: 9 maj 2020
 *      Author: wmarkowski
 */

#ifndef COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_CUSTOMDASHBOARD_H_
#define COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_CUSTOMDASHBOARD_H_

#include <Adafruit_SSD1306.h>
#include <com/github/wmarkow/bike/drivers/gauge/StepperGauge.h>
#include <com/github/wmarkow/bike/drivers/speed/SpeedSensor.h>

class CustomDashboard
{
private:
   Adafruit_SSD1306 display;
   StepperGauge speedGauge;
   SpeedSensor speedSensor;
   bool speedSensorEnabled;

   void testdrawline();
   void testdrawchar();

public:
   CustomDashboard();
   void init();
   void loop();
   void reset();
   void tickSpeedSensor(unsigned long millis);
   void setSpeed(uint8_t speed);
};

#endif /* COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_CUSTOMDASHBOARD_H_ */
