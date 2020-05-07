/*
 * AirCoreGauge.h
 *
 *  Created on: 3 pa� 2019
 *      Author: wmarkowski
 */

#ifndef AIRCOREGAUGE_H_
#define AIRCOREGAUGE_H_

#include <stdint.h>
#include "AbstractGauge.h"
#include "../mlx/MLX10407.h"

class AirCoreGauge : public AbstractGauge
{
private:
    MLX10407* driver;
    uint8_t logoNumber;

protected:
    void updateDriverDelta(int16_t deltaAngle);
    void updateDriverAbsolute(int16_t currentAngle);

public:
    AirCoreGauge(MLX10407* driver, uint8_t logoNumber);
};

#endif /* AIRCOREGAUGE_H_ */
