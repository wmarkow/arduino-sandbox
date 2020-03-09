/*
 * StepperGauge.h
 *
 *  Created on: 3 mar 2020
 *      Author: wmarkowski
 */

#ifndef STEPPERGAUGE_H_
#define STEPPERGAUGE_H_

#include "AbstractGauge.h"

class StepperGauge : public AbstractGauge
{
protected:
    void updateDriverDelta(int16_t deltaAngle);
    void updateDriverAbsolute(int16_t currentAngle);

public:
    StepperGauge();
    void init();
};

#endif /* STEPPERGAUGE_H_ */
