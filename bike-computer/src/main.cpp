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
#include "GaugeCommand.h"

#define FIRST_MLS10407_CS 7
#define SECOND_MLS10407_CS 5

MLX10407 gauge1(FIRST_MLS10407_CS);
MLX10407 gauge2(SECOND_MLS10407_CS);

FixedSizeArray<AbstractCommand*, 5> commands;
Array<AbstractCommand*> *commandsArray = &commands;
Terminal terminal(&Serial, commandsArray);
GaugeCommand gaugeCommand;

void demo();

void setup()
{
    Serial.begin(9600);
    gauge1.init();
    gauge2.init();

    commandsArray->add(&gaugeCommand);

    demo();
}

void loop(void)
{
    terminal.loop();
}

void demo()
{
    int i = 0;

    for (i = 0; i < 360; i++)
    {
        gauge1.writeLogo(1, i);
        delayMicroseconds(5);
        gauge1.writeLogo(2, i);
        gauge2.writeLogo(1, i);

        // A delay is also useful for preventing erratic needle slap and
        // good continuity between values.
        delay(10);
    }
    delay(1000);

    for (i = 359; i >= 0; i--)
    {
        gauge1.writeLogo(1, i);
        delayMicroseconds(5);
        gauge1.writeLogo(2, i);
        gauge2.writeLogo(1, i);

        delay(10);
    }
    delay(1000);
}
