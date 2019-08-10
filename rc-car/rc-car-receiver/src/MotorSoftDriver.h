/*
 * MotorSoftDriver.h
 *
 *  Created on: 6 sie 2019
 *      Author: Witold Markowski
 */

#ifndef MOTORSOFTDRIVER_H_
#define MOTORSOFTDRIVER_H_

#include <stdint.h>
#include <L298N.h>

class MotorSoftDriver
{
private:
    /**
     * From -255 to 255, just to easy control PWM
     */
    int16_t desiredSpeed;
    /**
     * From -255 to 255, just to easy control PWM
     */
    int16_t currentSpeed;
    unsigned long lastUpdateTimeMillis;
    L298N motor;
public:
    MotorSoftDriver(uint8_t pinEnable, uint8_t pinIN1, uint8_t pinIN2);
    /***
     * From -100 to 100
     */
    void setSpeedInPercent(int8_t speedInPercent);
    void init();
    void loop();

};

#endif /* MOTORSOFTDRIVER_H_ */
