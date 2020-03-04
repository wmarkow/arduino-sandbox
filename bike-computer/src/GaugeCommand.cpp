/*
 * GaugeCommand.cpp
 *
 *  Created on: 1 paü 2019
 *      Author: wmarkowski
 */

#include "GaugeCommand.h"
#include <avr/pgmspace.h>
#include <Arduino.h>
#include <CommandParams.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <WString.h>

#include "AirCoreGauge.h"
#include "StepperGauge.h"

extern AirCoreGauge tempGauge;
extern AirCoreGauge speedGauge;
extern AirCoreGauge fuelGauge;
extern StepperGauge stepperGauge;

const __FlashStringHelper* GaugeCommand::getName()
{
    return F("gauge");
}

void GaugeCommand::process(CommandParams *params, HardwareSerial *serial)
{
    lastProcessTime = millis();

    if (params->getNumberOfParameters() == 3)
    {
        String gaugeNumberAsString = params->getParam(1);
        uint8_t gaugeNumber = gaugeNumberAsString.toInt();

        String geugeValueAsString = params->getParam(2);
        int16_t gaugeValue = geugeValueAsString.toInt();

        if (gaugeNumber == 0)
        {
            tempGauge.setAngle(gaugeValue);
        }
        else if (gaugeNumber == 1)
        {
            speedGauge.setAngle(gaugeValue);
        }
        else if (gaugeNumber == 2)
        {
            fuelGauge.setAngle(gaugeValue);
        }else if (gaugeNumber == 3)
        {
            stepperGauge.setAngle(gaugeValue);
        }
    }
}

void GaugeCommand::processBackground(HardwareSerial *serial)
{
    unsigned long currentMillis = millis();
    if (currentMillis < lastProcessTime + 1000L)
    {
        return;
    }

    lastProcessTime = currentMillis;
}
