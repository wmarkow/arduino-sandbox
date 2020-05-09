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

#include <com/github/wmarkow/bike/drivers/gauge/StepperGauge.h>
#include <com/github/wmarkow/bike/drivers/speed/SpeedSensor.h>
#include <com/github/wmarkow/bike/dashboards/custom/CustomDashboard.h>
#include <com/github/wmarkow/bike/dashboards/pantheon/PantheonDashCommand.h>

#define WHEEL_SENSOR_PIN 2

CustomDashboard customDashboard;

FixedSizeArray<AbstractCommand*, 5> commands;
Array<AbstractCommand*> *commandsArray = &commands;
Terminal terminal(&Serial, commandsArray);
PantheonDashCommand dashCommand;

void onSpeedSensorEvent();

void setup()
{
   Serial.begin(9600);
   commandsArray->add(&dashCommand);

   customDashboard.init();

   pinMode(WHEEL_SENSOR_PIN, INPUT_PULLUP);
   attachPCINT(digitalPinToPCINT(WHEEL_SENSOR_PIN), onSpeedSensorEvent,
         FALLING);
}

void loop(void)
{
   terminal.loop();
   customDashboard.loop();
}

void onSpeedSensorEvent()
{
   customDashboard.tickSpeedSensor(millis());

//   uint8_t speed = speedSensor.getSpeed();
//   float acceleration = speedSensor.getAcceleration();
//
//   Serial.print(speed);
//   Serial.print("   ");
//   Serial.println(acceleration);
}
