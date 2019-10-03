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
    uint16_t minAngle;
    uint16_t maxAngle;
    uint16_t minValue;
    uint16_t maxValue;
    unsigned long lastUpdateTimeMillis;

public:
    AirCoreGauge(MLX10407* driver, uint8_t logoNumber);
    void init();
    void loop();
    void setAngle(uint16_t angle);
    void setMin(uint16_t angle, uint16_t value);
    void setMax(uint16_t angle, uint16_t value);
    void setValue(uint16_t value);
};

#endif /* AIRCOREGAUGE_H_ */
