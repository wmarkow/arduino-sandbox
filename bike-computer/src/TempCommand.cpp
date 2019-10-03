/*
 * TempCommand.cpp
 *
 *  Created on: 3 paü 2019
 *      Author: wmarkowski
 */

#include "TempCommand.h"

#include <avr/pgmspace.h>
#include <Arduino.h>
#include <CommandParams.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <WString.h>

#include "AirCoreGauge.h"

extern AirCoreGauge tempGauge;

const __FlashStringHelper* TempCommand::getName()
{
    return F("temp");
}

void TempCommand::process(CommandParams *params, HardwareSerial *serial)
{
    if (params->getNumberOfParameters() == 2)
    {
        String tempAsString = params->getParam(1);
        uint16_t temp = tempAsString.toInt();

        tempGauge.setValue(temp);
    }
}

void TempCommand::processBackground(HardwareSerial *serial)
{
}
