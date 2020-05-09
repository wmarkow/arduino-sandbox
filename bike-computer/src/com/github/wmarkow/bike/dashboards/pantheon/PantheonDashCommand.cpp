/*
 * DashCommand.cpp
 *
 *  Created on: 5 pa� 2019
 *      Author: wmarkowski
 */

#include <avr/pgmspace.h>
#include <Arduino.h>
#include <com/github/wmarkow/bike/dashboards/pantheon/PantheonDashCommand.h>
#include <CommandParams.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <WString.h>

#include "com/github/wmarkow/bike/drivers/gauge/AirCoreGauge.h"
#include "com/github/wmarkow/bike/drivers/backlight/Backlight.h"
#include "Demo.h"

//extern AirCoreGauge speedGauge;
//extern AirCoreGauge tempGauge;
//extern AirCoreGauge fuelGauge;
//extern Backlight backlight;

const __FlashStringHelper* PantheonDashCommand::getName()
{
    return F("dash");
}

void PantheonDashCommand::process(CommandParams *params, HardwareSerial *serial)
{
    if (params->getNumberOfParameters() == 2)
    {
        String subcommand = params->getParam(1);

        if (subcommand.equals("--help"))
        {
            printUsage(serial);

            return;
        }
        if (subcommand.equals("demo"))
        {
//            demo();

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
//            speedGauge.setValue(value);
        }
        else if (subcommand.equals("temp"))
        {
//            tempGauge.setValue(value);
        }
        else if (subcommand.equals("fuel"))
        {
//            fuelGauge.setValue(value);
        }
        else if (subcommand.equals("backlight"))
        {
//            backlight.setValuePercent(value);
        }
    }
}

void PantheonDashCommand::processBackground(HardwareSerial *serial)
{
}

void PantheonDashCommand::printUsage(HardwareSerial *serial)
{
    serial->println(F("Usage: dash  speed     <0-100>"));
    serial->println(F("Usage: dash  temp      <0-100>"));
    serial->println(F("Usage: dash  fuel      <0-100>"));
    serial->println(F("Usage: dash  backlight <0-100>"));
    serial->println(F("Usage: dash  demo"));
}
