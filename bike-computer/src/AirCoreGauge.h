/*
 * AirCoreGauge.h
 *
 *  Created on: 3 paü 2019
 *      Author: wmarkowski
 */

#ifndef AIRCOREGAUGE_H_
#define AIRCOREGAUGE_H_

#include <stdint.h>
#include "MLX10407.h"

class AirCoreGauge
{
private:
    MLX10407* driver;
    uint8_t logoNumber;
    uint16_t currentAngle;
    uint16_t desiredAngle;
    unsigned long lastUpdateTimeMillis;

public:
    AirCoreGauge(MLX10407* driver, uint8_t logoNumber);
    void init();
    void loop();
    void setAngle(uint16_t angle);
};

#endif /* AIRCOREGAUGE_H_ */
