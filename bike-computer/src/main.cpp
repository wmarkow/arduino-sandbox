/*
 * main.cpp
 *
 *  Created on: 26 wrz 2019
 *      Author: wmarkow
 */

#include <Arduino.h>
#include <Terminal.h>
#include <Array.h>
#include <FixedSizeArray.h>
#include <HardwareSerial.h>

#include "MLX10407.h"
#include "AirCoreGauge.h"
#include "GaugeCommand.h"
#include "SpeedCommand.h"
#include "TempCommand.h"
#include "FuelCommand.h"

#define FIRST_MLS10407_CS 7
#define SECOND_MLS10407_CS 5

MLX10407 gauge1(FIRST_MLS10407_CS);
MLX10407 gauge2(SECOND_MLS10407_CS);

AirCoreGauge tempGauge(&gauge1, 1);
AirCoreGauge speedGauge(&gauge1, 2);
AirCoreGauge fuelGauge(&gauge2, 1);

FixedSizeArray<AbstractCommand*, 5> commands;
Array<AbstractCommand*> *commandsArray = &commands;
Terminal terminal(&Serial, commandsArray);
GaugeCommand gaugeCommand;
SpeedCommand speedCommand;
TempCommand tempCommand;
FuelCommand fuelCommand;

void demo();

void setup()
{
    Serial.begin(9600);
    gauge1.init();
    gauge2.init();

    speedGauge.setAngleRange(3, 260);
    speedGauge.setValueRange(0, 160);

    tempGauge.setAngleRange(-90, 90);
    tempGauge.setValueRange(0, 100);

    fuelGauge.setAngleRange(-90, 90);
    fuelGauge.setValueRange(0, 100);

    commandsArray->add(&gaugeCommand);
    commandsArray->add(&speedCommand);
    commandsArray->add(&tempCommand);
    commandsArray->add(&fuelCommand);

    demo();
}

void loop(void)
{
    terminal.loop();

    tempGauge.loop();
    speedGauge.loop();
    fuelGauge.loop();
}

void demo()
{
    tempGauge.setAnglePercents(100);
    speedGauge.setAnglePercents(100);
    fuelGauge.setAnglePercents(100);

    while (tempGauge.isAdjusting() || speedGauge.isAdjusting()
            || fuelGauge.isAdjusting())
    {
        loop();
    }

    delay(100);

    tempGauge.setAnglePercents(0);
    speedGauge.setAnglePercents(0);
    fuelGauge.setAnglePercents(0);
}
