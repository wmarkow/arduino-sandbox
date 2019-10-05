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
    int16_t currentAngle;
    int16_t desiredAngle;
    int16_t minAngle;
    int16_t maxAngle;
    int16_t minValue;
    int16_t maxValue;
    unsigned long lastUpdateTimeMillis;

public:
    AirCoreGauge(MLX10407* driver, uint8_t logoNumber);
    void init();
    void loop();
    void setAngleRange(int16_t min, int16_t max);
    void setAngle(int16_t angle);
    void setAnglePercents(uint8_t percents);
    void setValueRange(int16_t min, int16_t max);
    void setValue(int16_t value);

    void setMin(int16_t angle, int16_t value);
    void setMax(int16_t angle, int16_t value);

    boolean isAdjusting();
};

#endif /* AIRCOREGAUGE_H_ */
