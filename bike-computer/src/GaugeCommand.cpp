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

extern MLX10407 gauge;

const __FlashStringHelper* GaugeCommand::getName()
{
    return F("gauge");
}

void GaugeCommand::process(CommandParams *params, HardwareSerial *serial)
{
    lastProcessTime = millis();

    if (params->getNumberOfParameters() == 3)
    {
        String geugeNumberAsString = params->getParam(1);
        uint8_t gaugeNumber = geugeNumberAsString.toInt();

        String geugeValueAsString = params->getParam(2);
        uint16_t gaugeValue = geugeValueAsString.toInt();

//        String geugeQuadrantAsString = params->getParam(3);
//        uint8_t gaugeQuadrant = geugeQuadrantAsString.toInt();

        gauge.setGauge(gaugeNumber, gaugeValue);
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
