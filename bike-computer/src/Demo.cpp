/*
 * Demo.cpp
 *
 *  Created on: 17 lis 2019
 *      Author: wmarkowski
 */

#include "AirCoreGauge.h"
#include "Backlight.h"
#include "Demo.h"

extern AirCoreGauge speedGauge;
extern AirCoreGauge tempGauge;
extern AirCoreGauge fuelGauge;
extern Backlight backlight;

void demo()
{
    speedGauge.setAnglePercents(0);
    tempGauge.setAnglePercents(0);
    fuelGauge.setAnglePercents(0);
    while (tempGauge.isAdjusting() || speedGauge.isAdjusting()
            || fuelGauge.isAdjusting())
    {
        demoLoop();
    }

    for (int8_t perc = 0; perc <= 100; perc++)
    {
        tempGauge.setAnglePercents(perc);
        speedGauge.setAnglePercents(perc);
        fuelGauge.setAnglePercents(perc);
        backlight.setValuePercent(perc);

        while (tempGauge.isAdjusting() || speedGauge.isAdjusting()
                || fuelGauge.isAdjusting())
        {
            demoLoop();
        }
    }

    delay(200);

    for (int8_t perc = 100; perc >= 0; perc--)
    {
        tempGauge.setAnglePercents(perc);
        speedGauge.setAnglePercents(perc);
        fuelGauge.setAnglePercents(perc);
        backlight.setValuePercent(perc);

        while (tempGauge.isAdjusting() || speedGauge.isAdjusting()
                || fuelGauge.isAdjusting())
        {
            demoLoop();
        }
    }
}

void demoLoop()
{
    tempGauge.loop();
    speedGauge.loop();
    fuelGauge.loop();
}
