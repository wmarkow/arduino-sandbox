/*
 * AirCoreGauge.cpp
 *
 *  Created on: 3 paŸ 2019
 *      Author: wmarkowski
 */

#include "AirCoreGauge.h"

AirCoreGauge::AirCoreGauge(MLX10407* driver, uint8_t logoNumber) : AbstractGauge()
{
    this->driver = driver;
    this->logoNumber = logoNumber;
}

void AirCoreGauge::updateDriverDelta(int16_t deltaAngle)
{
	// nothing to do here; do not support delta update
}

void AirCoreGauge::updateDriverAbsolute(int16_t currentAngle)
{
	driver->writeLogo(logoNumber, currentAngle);
}
