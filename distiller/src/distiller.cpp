/*
 * distiller.cpp
 *
 *  Created on: 7 lut 2021
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "drivers/WaterFlowSensor.h"

#define WATER_FLOW_SENSOR_PIN 2
#define TERMOMETER_PIN 3

WaterFlowSensor waterFlowSensor(WATER_FLOW_SENSOR_PIN);

OneWire oneWireBus(TERMOMETER_PIN);
DallasTemperature thermometerBus(&oneWireBus);

unsigned long lastCheckTime;

void water_sensor_event();

void setup()
{
   Serial.begin(115200);

   waterFlowSensor.init();

   attachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR_PIN),
         water_sensor_event, RISING);

   lastCheckTime = millis();

   thermometerBus.begin();
   thermometerBus.setWaitForConversion(true);

   if (thermometerBus.getDeviceCount() == 1)
   {
      Serial.println("DS18B20 thermometer found");

      thermometerBus.setResolution(9);
   }
   else
   {
      Serial.println("DS18B20 thermometer NOT found!");
   }
}

void loop()
{
   waterFlowSensor.loop();

   unsigned long measureSpanMillis = millis() - lastCheckTime;

   if (measureSpanMillis >= 1000L)
   {
      // display water flow
      Serial.print(waterFlowSensor.getRpm());
      Serial.print(" ; ");

      // display temperature
      thermometerBus.requestTemperatures();
      float temp = thermometerBus.getTempCByIndex(0);
      if (temp == DEVICE_DISCONNECTED_C)
      {
         Serial.print("ERR");
      }
      else
      {
         Serial.print(temp);
      }
      Serial.print(" ; ");

      // display time span
      Serial.println(measureSpanMillis);
      lastCheckTime = millis();
   }
}

void water_sensor_event()
{
   waterFlowSensor.tick();
}
