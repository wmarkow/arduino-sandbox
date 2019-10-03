/*
 * SpeedCommand.cpp
 *
 *  Created on: 3 paü 2019
 *      Author: wmarkowski
 */

#include "SpeedCommand.h"

#include <avr/pgmspace.h>
#include <Arduino.h>
#include <CommandParams.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <WString.h>

#include "AirCoreGauge.h"

extern AirCoreGauge speedGauge;

const __FlashStringHelper* SpeedCommand::getName()
{
    return F("speed");
}

void SpeedCommand::process(CommandParams *params, HardwareSerial *serial)
{
    if (params->getNumberOfParameters() == 2)
    {
        String speedAsString = params->getParam(1);
        uint16_t speed = speedAsString.toInt();

        speedGauge.setValue(speed);
    }
}

void SpeedCommand::processBackground(HardwareSerial *serial)
{
}

