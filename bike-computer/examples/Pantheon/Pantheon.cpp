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

#include <com/github/wmarkow/bike/dashboards/pantheon/PantheonDashCommand.h>
#include <com/github/wmarkow/bike/dashboards/pantheon/PantheonDashboard.h>

#define WHEEL_SENSOR_PIN 2

PantheonDashboard pantheonDashboard;

FixedSizeArray<AbstractCommand*, 5> commands;
Array<AbstractCommand*> *commandsArray = &commands;
Terminal terminal(&Serial, commandsArray);
DashCommand dashCommand;

void onSpeedSensorEvent();

void setup()
{
   Serial.begin(9600);

   commandsArray->add(&dashCommand);

   pantheonDashboard.init();

   pinMode(WHEEL_SENSOR_PIN, INPUT_PULLUP);
   attachPCINT(digitalPinToPCINT(WHEEL_SENSOR_PIN), onSpeedSensorEvent,
   FALLING);
}

void loop(void)
{
   terminal.loop();
   pantheonDashboard.loop();
}

void onSpeedSensorEvent()
{
   pantheonDashboard.tickSpeedSensor(millis());
}
