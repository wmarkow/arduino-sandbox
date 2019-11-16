/*
 * Demo.cpp
 *
 *  Created on: 17 lis 2019
 *      Author: wmarkowski
 */

#include "AirCoreGauge.h"
#include "Demo.h"
#include "main.h"

extern AirCoreGauge speedGauge;
extern AirCoreGauge tempGauge;
extern AirCoreGauge fuelGauge;

void demo()
{
    speedGauge.setAnglePercents(0);
    tempGauge.setAnglePercents(0);
    fuelGauge.setAnglePercents(0);
    while (tempGauge.isAdjusting() || speedGauge.isAdjusting()
            || fuelGauge.isAdjusting())
    {
        loop0();
    }

    for (int8_t perc = 0; perc <= 100; perc++)
    {
        tempGauge.setAnglePercents(perc);
        speedGauge.setAnglePercents(perc);
        fuelGauge.setAnglePercents(perc);

        while (tempGauge.isAdjusting() || speedGauge.isAdjusting()
                || fuelGauge.isAdjusting())
        {
            loop0();
        }
    }

    delay(200);

    for (int8_t perc = 100; perc >= 0; perc--)
    {
        tempGauge.setAnglePercents(perc);
        speedGauge.setAnglePercents(perc);
        fuelGauge.setAnglePercents(perc);

        while (tempGauge.isAdjusting() || speedGauge.isAdjusting()
                || fuelGauge.isAdjusting())
        {
            loop0();
        }
    }
}

