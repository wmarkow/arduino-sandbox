/*
 * AbstractGauge.h
 *
 *  Created on: 9 mar 2020
 *      Author: wmarkowski
 */

#ifndef ABSTRACTGAUGE_H_
#define ABSTRACTGAUGE_H_

#include <stdint.h>

class AbstractGauge
{
private:
    int16_t currentAngle;
    int16_t desiredAngle;
    int16_t minAngle;
    int16_t maxAngle;
    int16_t minValue;
    int16_t maxValue;
    unsigned long lastUpdateTimeMillis;

protected:
    virtual void updateDriverDelta(int16_t deltaAngle) = 0;
    virtual void updateDriverAbsolute(int16_t currentAngle) = 0;

public:
    AbstractGauge();
    void init();
    void loop();
    void setAngleRange(int16_t min, int16_t max);
    void setAngle(int16_t angle);
    void setAnglePercents(uint8_t percents);
    void setValueRange(int16_t min, int16_t max);
    void setValue(int16_t value);

    void setMin(int16_t angle, int16_t value);
    void setMax(int16_t angle, int16_t value);

    bool isAdjusting();
};

#endif /* ABSTRACTGAUGE_H_ */
