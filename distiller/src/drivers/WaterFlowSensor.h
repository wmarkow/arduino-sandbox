/*
 * WaterFlowSensor.h
 *
 *  Created on: 14 lut 2021
 *      Author: wmarkowski
 */

#ifndef SRC_DRIVERS_WATERFLOWSENSOR_H_
#define SRC_DRIVERS_WATERFLOWSENSOR_H_

#include <stdint.h>

class WaterFlowSensor
{
private:
  uint8_t pin;
  volatile uint16_t waterSensorCounter;
  unsigned long waterSensorMeasureBeginMillis;
  double rpm;
public:
   WaterFlowSensor(uint8_t pin);
   void init();
   void loop();
   void tick();
   double getRpm();
};



#endif /* SRC_DRIVERS_WATERFLOWSENSOR_H_ */
