/*
 * MotorSoftDriver.cpp
 *
 *  Created on: 6 sie 2019
 *      Author: wmarkowski
 */
#include "Arduino.h"
#include "MotorSoftDriver.h"

// Those two below define the max possible acceleration
#define MAX_DELTA_SPEED 255
#define MAX_DELTA_T_IN_MILLIS 500

#define DELTA_T_IN_MILLIS 10
#define DELTA_SPEED (int)((float)DELTA_T_IN_MILLIS * ((float)MAX_DELTA_SPEED / (float)MAX_DELTA_T_IN_MILLIS))

MotorSoftDriver::MotorSoftDriver(uint8_t pinEnable, uint8_t pinIN1,
        uint8_t pinIN2) :
        motor(pinEnable, pinIN1, pinIN2)
{
    this->currentSpeed = 0;
    this->desiredSpeed = 0;
    this->lastUpdateTimeMillis = 0;
}

void MotorSoftDriver::setSpeedInPercent(int8_t speedInPercent)
{
    this->desiredSpeed = map(speedInPercent, -100, 100, -255, 255);
}

void MotorSoftDriver::init()
{
    this->motor.setSpeed(0);
    this->motor.stop();
}

void MotorSoftDriver::loop()
{
    if (millis() - lastUpdateTimeMillis < DELTA_T_IN_MILLIS)
    {
        return;
    }

    if (currentSpeed < desiredSpeed)
    {
        currentSpeed += DELTA_SPEED;
        if (currentSpeed >= desiredSpeed)
        {
            currentSpeed = desiredSpeed;
        }
    }
    else if (desiredSpeed < currentSpeed)
    {
        currentSpeed -= DELTA_SPEED;
        if (currentSpeed <= desiredSpeed)
        {
            currentSpeed = desiredSpeed;
        }
    }

    if (currentSpeed > 255)
    {
        currentSpeed = 255;
    }
    else if (currentSpeed < -255)
    {
        currentSpeed = -255;
    }

    if (currentSpeed == 0)
    {
        motor.setSpeed(0);
        motor.stop();
    }
    else if (currentSpeed > 0)
    {
        motor.setSpeed(currentSpeed);
        motor.forward();
    }
    else if (currentSpeed < 0)
    {
        motor.setSpeed(-currentSpeed);
        motor.backward();
    }

    lastUpdateTimeMillis = millis();
}

