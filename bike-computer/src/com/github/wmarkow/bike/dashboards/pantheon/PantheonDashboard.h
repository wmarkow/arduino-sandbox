/*
 * PantheonDashboard.h
 *
 *  Created on: 9 maj 2020
 *      Author: wmarkowski
 */

#ifndef COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_PANTHEON_PANTHEONDASHBOARD_H_
#define COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_PANTHEON_PANTHEONDASHBOARD_H_

#include <com/github/wmarkow/bike/drivers/backlight/Backlight.h>
#include <com/github/wmarkow/bike/drivers/gauge/AirCoreGauge.h>
#include <com/github/wmarkow/bike/drivers/mlx/MLX10407.h>
#include <com/github/wmarkow/bike/drivers/speed/SpeedSensor.h>

class PantheonDashboard
{
private:
   MLX10407 gauge1;
   MLX10407 gauge2;

   AirCoreGauge tempGauge;
   AirCoreGauge speedGauge;
   AirCoreGauge fuelGauge;
   Backlight backlight;
   SpeedSensor speedSensor;

public:
   PantheonDashboard();
   void init();
   void loop();
   void tickSpeedSensor(unsigned long millis);
};

#endif /* COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_PANTHEON_PANTHEONDASHBOARD_H_ */
