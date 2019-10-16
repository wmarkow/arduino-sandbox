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
    unsigned long tickInMillis;
    unsigned long previousTickInMillis;
    uint8_t wheelDiameterInInches;
public:
    SpeedSensor();
    void tick(unsigned long currentMillis);
    void setWheelDiamieter(uint8_t diameterInInches);
    uint8_t getSpeed();
};



#endif /* SPEEDSENSOR_H_ */
