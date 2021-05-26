/*
 * WheelSensor.h
 *
 *  Created on: 16 Oct 2019
 *      Author: wmarkowski
 */

#ifndef WHEELSENSOR_H_
#define WHEELSENSOR_H_

#include <stdint.h>

class WheelSensor
{
private:
    unsigned long t0;
    unsigned long t1;
    unsigned long t2;
    uint32_t initialTotalDistanceInM;
    uint8_t wheelDiameterInInches;
    uint16_t tickCount;

public:
    WheelSensor();
    void tick(unsigned long currentMillis);
    void setWheelDiameter(uint8_t diameterInInches);
    float getSpeed();
    float getAcceleration();
    uint32_t getTripDistance();
    void resetTripDistance(uint32_t initialTotalDistanceInM);
    uint32_t getTotalDistance();
};



#endif /* WHEELSENSOR_H_ */
