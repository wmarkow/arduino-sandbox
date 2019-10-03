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

    speedGauge.setMin(3, 0);
    speedGauge.setMax(260, 160);

    tempGauge.setMin(-90, 0);
    tempGauge.setMax(90, 100);

    fuelGauge.setMin(-90, 0);
    fuelGauge.setMax(90, 100);

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

    tempGauge.setValuePercents(100);
    speedGauge.setValuePercents(100);
    fuelGauge.setValuePercents(100);

    while (tempGauge.isAdjusting() || speedGauge.isAdjusting() || fuelGauge.isAdjusting())
    {
        loop();
    }

    delay(100);

    tempGauge.setValuePercents(0);
    speedGauge.setValuePercents(0);
    fuelGauge.setValuePercents(0);
}
