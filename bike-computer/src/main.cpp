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
#include <PinChangeInterrupt.h>

#include "MLX10407.h"
#include "AirCoreGauge.h"
#include "GaugeCommand.h"
#include "DashCommand.h"
#include "SpeedSensor.h"

#define FIRST_MLS10407_CS 7
#define SECOND_MLS10407_CS 5
#define WHEEL_SENSOR_PIN A2
#define CADENCE_SENSOR_PIN A3

MLX10407 gauge1(FIRST_MLS10407_CS);
MLX10407 gauge2(SECOND_MLS10407_CS);

AirCoreGauge tempGauge(&gauge1, 1);
AirCoreGauge speedGauge(&gauge1, 2);
AirCoreGauge fuelGauge(&gauge2, 1);

FixedSizeArray<AbstractCommand*, 5> commands;
Array<AbstractCommand*> *commandsArray = &commands;
Terminal terminal(&Serial, commandsArray);
GaugeCommand gaugeCommand;
DashCommand dashCommand;

SpeedSensor speedSensor;

volatile unsigned long lastWheelEventMillis = 0;
volatile unsigned long lastCadenceEventMillis = 0;

void loop0();
void demo();
void onWheelSensorEvent();
void onCadenceSensorEvent();

void setup()
{
    pinMode(WHEEL_SENSOR_PIN, INPUT_PULLUP);
    pinMode(CADENCE_SENSOR_PIN, INPUT_PULLUP);
    attachPCINT(digitalPinToPCINT(WHEEL_SENSOR_PIN), onWheelSensorEvent,
    FALLING);
    attachPCINT(digitalPinToPCINT(CADENCE_SENSOR_PIN), onCadenceSensorEvent,
    FALLING);

    speedSensor.setWheelDiamieter(24);

    Serial.begin(9600);
    gauge1.init();
    gauge2.init();

    speedGauge.setAngleRange(3, 260);
    speedGauge.setValueRange(0, 160);

    tempGauge.setAngleRange(-90, 90);
    tempGauge.setValueRange(0, 40);

    fuelGauge.setAngleRange(-90, 90);
    fuelGauge.setValueRange(0, 100);

    commandsArray->add(&gaugeCommand);
    commandsArray->add(&dashCommand);

    demo();
}

void loop(void)
{
    loop0();

    uint8_t speed = speedSensor.getSpeed();
    tempGauge.setValue(speed);
}

void loop0()
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
        loop0();
    }

    delay(100);

    tempGauge.setAnglePercents(0);
    speedGauge.setAnglePercents(0);
    fuelGauge.setAnglePercents(0);
}

void onWheelSensorEvent()
{
    speedSensor.tick(millis());

    uint8_t speed = speedSensor.getSpeed();
    float acceleration = speedSensor.getAcceleration();

    Serial.print(speed);
    Serial.print("   ");
    Serial.println(acceleration);
}

void onCadenceSensorEvent()
{
    Serial.println(F("cadence event"));
}
