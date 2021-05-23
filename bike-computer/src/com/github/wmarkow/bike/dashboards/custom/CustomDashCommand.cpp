/*
 * CustomDashCommand.cpp
 *
 *  Created on: 9 maj 2020
 *      Author: wmarkowski
 */

#include "CustomDashCommand.h"

CustomDashCommand::CustomDashCommand(CustomDashboard *dashboard)
{
    this->dashboard = dashboard;
}

const __FlashStringHelper* CustomDashCommand::getName()
{
    return F("dash");
}

void CustomDashCommand::process(CommandParams *params, HardwareSerial *serial)
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
        if (subcommand.equals("reset"))
        {
            dashboard->reset();
        }
        if (subcommand.equals("eeprom"))
        {
            // print EEPROM
            for(uint8_t q = 0 ; q < sizeof(EEPROMData) ; q ++)
            {
                uint8_t data = EEPROM[q];
                Serial.print(data, HEX);
                Serial.print(" ");
            }
            Serial.println();
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
            dashboard->setSpeed(value);
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

void CustomDashCommand::processBackground(HardwareSerial *serial)
{
}

void CustomDashCommand::printUsage(HardwareSerial *serial)
{
    serial->println(F("dash reset"));
    serial->println(F("dash speed <0-60>"));
    serial->println(F("dash eeprom"));
}
