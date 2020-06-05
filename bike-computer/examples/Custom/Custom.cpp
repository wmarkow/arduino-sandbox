/*
 * main.cpp
 *
 *  Created on: 26 wrz 2019
 *      Author: wmarkow
 */


#include <Arduino.h>
#include <Array.h>
#include <com/github/wmarkow/bike/dashboards/custom/CustomDashboard.h>
#include <com/github/wmarkow/bike/dashboards/custom/CustomDashCommand.h>
#include <FixedSizeArray.h>
#include <HardwareSerial.h>
#include <PinChangeInterrupt.h>
#include <Print.h>
#include <stdint.h>
#include <Terminal.h>
#include <Wire.h>
#include <WString.h>

#define WHEEL_SENSOR_PIN 2

CustomDashboard customDashboard;

FixedSizeArray<AbstractCommand*, 5> commands;
Array<AbstractCommand*> *commandsArray = &commands;
Terminal terminal(&Serial, commandsArray);
CustomDashCommand dashCommand(&customDashboard);

void onSpeedSensorEvent();
void scanI2C();

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
}

void scanI2C()
{
   byte error, address;
   int nDevices;

   Serial.println("Scanning...");

   nDevices = 0;
   for (address = 1; address < 127; address++)
   {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0)
      {
         Serial.print("I2C device found at address 0x");
         if (address < 16)
         {
            Serial.print("0");
         }
         Serial.print(address, HEX);
         Serial.println("  !");

         nDevices++;
      }
      else if (error == 4)
      {
         Serial.print("Unknown error at address 0x");
         if (address < 16)
         {
            Serial.print("0");
         }
         Serial.println(address, HEX);
      }
   }
   if (nDevices == 0)
   {
      Serial.println("No I2C devices found\n");
   }
   else
   {
      Serial.println("done\n");
   }
}
