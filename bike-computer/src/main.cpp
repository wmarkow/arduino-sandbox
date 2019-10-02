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

MLX10407 gauge;

FixedSizeArray<AbstractCommand*, 5> commands;
Array<AbstractCommand*> *commandsArray = &commands;
Terminal terminal(&Serial, commandsArray);
GaugeCommand gaugeCommand;

void demo();

void setup()
{
    Serial.begin(9600);
    gauge.init();

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
        gauge.setGauge(0, i);
//        // You need at least 5us between transfers or the needles get unstable
//        delayMicroseconds(5);
//        gauge.setGauge(1, i);

// A 1ms delay is also useful for preventing erratic needle slap and
// good continuity between values.
        delay(10);
//        Serial.println(i);
    }
    delay(1000);

    for (i = 359; i >= 0; i--)
    {
        gauge.setGauge(0, i);
//        delayMicroseconds(5);
//        gauge.setGauge(1, i);
        delay(10);
    }
    delay(1000);
}
