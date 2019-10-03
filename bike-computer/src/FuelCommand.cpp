/*
 * FuelCommand.cpp
 *
 *  Created on: 3 paü 2019
 *      Author: wmarkowski
 */

#include "FuelCommand.h"

#include <avr/pgmspace.h>
#include <Arduino.h>
#include <CommandParams.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <WString.h>

#include "AirCoreGauge.h"

extern AirCoreGauge fuelGauge;

const __FlashStringHelper* FuelCommand::getName()
{
    return F("fuel");
}

void FuelCommand::process(CommandParams *params, HardwareSerial *serial)
{
    if (params->getNumberOfParameters() == 2)
    {
        String fuelAsString = params->getParam(1);
        uint16_t fuel = fuelAsString.toInt();

        fuelGauge.setValue(fuel);
    }
}

void FuelCommand::processBackground(HardwareSerial *serial)
{
}

