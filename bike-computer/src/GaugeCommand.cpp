/*
 * GaugeCommand.cpp
 *
 *  Created on: 1 pa� 2019
 *      Author: wmarkowski
 */

#include "GaugeCommand.h"
#include <avr/pgmspace.h>
#include <Arduino.h>
#include <CommandParams.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <WString.h>

#include "com/github/wmarkow/bike/drivers/gauge/AirCoreGauge.h"
#include "com/github/wmarkow/bike/drivers/gauge/StepperGauge.h"

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

    if (params->getNumberOfParameters() == 2)
	{
		String subcommand = params->getParam(1);

		if (subcommand.equals("--help"))
		{
			printUsage(serial);

			return;
		}

		return;
	}

    if (params->getNumberOfParameters() == 3)
    {
        String gaugeNumberAsString = params->getParam(1);
        uint8_t gaugeNumber = gaugeNumberAsString.toInt();

        String gaugeValueAsString = params->getParam(2);
        if (gaugeValueAsString.equals("reset"))
        {
            reset(gaugeNumber);

            return;
        }

        int16_t gaugeValue = gaugeValueAsString.toInt();

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

void GaugeCommand::reset(uint8_t gaugeNumber)
{
	if (gaugeNumber == 0)
	{
		tempGauge.reset();
	}
	else if (gaugeNumber == 1)
	{
		speedGauge.reset();
	}
	else if (gaugeNumber == 2)
	{
		fuelGauge.reset();
	}else if (gaugeNumber == 3)
	{
		stepperGauge.reset();
	}
}

void GaugeCommand::printUsage(HardwareSerial *serial)
{
    serial->println(F("Usage: gauge <gauge number> <angle value>"));
    serial->println(F("Usage: gauge <gauge number> reset"));
}
