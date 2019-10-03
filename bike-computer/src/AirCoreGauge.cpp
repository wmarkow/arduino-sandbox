/*
 * AirCoreGauge.cpp
 *
 *  Created on: 3 paŸ 2019
 *      Author: wmarkowski
 */

#include "AirCoreGauge.h"

#define DELTA_T_IN_MILLIS 5
#define DELTA_ANGLE 1

AirCoreGauge::AirCoreGauge(MLX10407* driver, uint8_t logoNumber)
{
    this->driver = driver;
    this->logoNumber = logoNumber;
    this->currentAngle = 0;
    this->desiredAngle = 0;
    this->lastUpdateTimeMillis = 0;
}

void AirCoreGauge::init()
{

}

/***
 * Must be constantly called to make a proper movement of the needle.
 * With air core gauges there is a known issue, that the needle chooses the closest way
 * when moving from start point to the end point.
 * Example: with this coordinate system:
 *       N(90)
 * W(0)          E(180)
 *       S(270)
 *When moving from 0 degree to 270 degree two paths are possible:
 * <ul>
 * <il>a longer path clockwise from 0 to 270</il>
 * <il>a shorter path counterclockwise from 0 to 270</il>
 * </ul>
 * The air core gauge will choose automatically the shorter path, it may be clockwise or counterclockwise,
 * it depends on the gauge construction itself. This behavior may be unexpected.
 *
 * The purpose of this method is to provide a consistent way of the needle's movement. If the gauge's default
 * movement from 0 degree to 90 degree is clockwise,
 * then this method will assure that the move from 0 to 359 will be also clockwise, and the move from the 359
 * to 0 will be counterclockwise.
 */
void AirCoreGauge::loop()
{
    if (currentAngle == desiredAngle)
    {
        return;
    }

    if (millis() - lastUpdateTimeMillis <= DELTA_T_IN_MILLIS)
    {
        return;
    }

    if (currentAngle < desiredAngle)
    {
        currentAngle += DELTA_ANGLE;
        if (currentAngle >= desiredAngle)
        {
            currentAngle = desiredAngle;
        }
    }
    else if (currentAngle > desiredAngle)
    {
        currentAngle -= DELTA_ANGLE;
        if (currentAngle <= desiredAngle)
        {
            currentAngle = desiredAngle;
        }
    }

    driver->writeLogo(logoNumber, currentAngle);

    lastUpdateTimeMillis = millis();
}

/***
 * @param angle - from 0 to 359
 */
void AirCoreGauge::setAngle(uint16_t angle)
{
    if (angle > 359)
    {
        this->desiredAngle = 359;

        return;
    }

    this->desiredAngle = angle;
}

