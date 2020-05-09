/*
 * CustomDashboard.h
 *
 *  Created on: 9 maj 2020
 *      Author: wmarkowski
 */

#ifndef COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_CUSTOMDASHBOARD_H_
#define COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_CUSTOMDASHBOARD_H_

#include <com/github/wmarkow/bike/drivers/gauge/StepperGauge.h>
#include <com/github/wmarkow/bike/drivers/speed/SpeedSensor.h>

class CustomDashboard
{
private:
   StepperGauge speedGauge;
   SpeedSensor speedSensor;

public:
   void init();
   void loop();
   void tickSpeedSensor(unsigned long millis);
};

#endif /* COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_CUSTOMDASHBOARD_H_ */
