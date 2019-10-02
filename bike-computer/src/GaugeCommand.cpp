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

#include "MLX10407.h"

extern MLX10407 gauge1;
extern MLX10407 gauge2;

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
        uint16_t gaugeValue = geugeValueAsString.toInt();

        if (gaugeNumber == 0)
        {
            gauge1.setGauge(0, gaugeValue);
        }
        else if (gaugeNumber == 1)
        {
            gauge1.setGauge(1, gaugeValue);
        }
        else if (gaugeNumber == 2)
        {
            gauge2.setGauge(0, gaugeValue);
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
