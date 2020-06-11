/*
 * SpeedSensor.h
 *
 *  Created on: 16 Oct 2019
 *      Author: wmarkowski
 */

#ifndef SPEEDSENSOR_H_
#define SPEEDSENSOR_H_

#include <stdint.h>

class SpeedSensor
{
private:
    unsigned long t0;
    unsigned long t1;
    unsigned long t2;
    uint8_t wheelDiameterInInches;
    uint16_t tickCount;

public:
    SpeedSensor();
    void tick(unsigned long currentMillis);
    void setWheelDiameter(uint8_t diameterInInches);
    float getSpeed();
    float getAcceleration();
    float getTripDistance();
};



#endif /* SPEEDSENSOR_H_ */
