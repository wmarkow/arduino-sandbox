/*
 * DashCommand.cpp
 *
 *  Created on: 5 paü 2019
 *      Author: wmarkowski
 */

#include "DashCommand.h"

#include <avr/pgmspace.h>
#include <Arduino.h>
#include <CommandParams.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <WString.h>

#include "AirCoreGauge.h"
#include "Backlight.h"

extern AirCoreGauge speedGauge;
extern AirCoreGauge tempGauge;
extern AirCoreGauge fuelGauge;
extern Backlight backlight;

const __FlashStringHelper* DashCommand::getName()
{
    return F("dash");
}

void DashCommand::process(CommandParams *params, HardwareSerial *serial)
{
    if (params->getNumberOfParameters() == 2)
    {
        String subcommand = params->getParam(1);

        if (subcommand.equals("--help"))
        {
            printUsage(serial);

            return;
        }
    }

    if (params->getNumberOfParameters() == 3)
    {
        String subcommand = params->getParam(1);

        String valueAsString = params->getParam(2);
        uint16_t value = valueAsString.toInt();

        if (subcommand.equals("speed"))
        {
            speedGauge.setValue(value);
        }
        else if (subcommand.equals("temp"))
        {
            tempGauge.setValue(value);
        }
        else if (subcommand.equals("fuel"))
        {
            fuelGauge.setValue(value);
        }
        else if (subcommand.equals("backlight"))
        {
            backlight.setValuePercent(value);
        }
    }
}

void DashCommand::processBackground(HardwareSerial *serial)
{
}

void DashCommand::printUsage(HardwareSerial *serial)
{
    serial->println(F("Usage: dash speed      <0-100>"));
    serial->println(F("Usage: dash  temp      <0-100>"));
    serial->println(F("Usage: dash  fuel      <0-100>"));
    serial->println(F("Usage: dash  backlight <0-100>"));
}
