/*
 * distiller.cpp
 *
 *  Created on: 7 lut 2021
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include <DS18B20.h>
#include "drivers/WaterFlowSensor.h"

#define WATER_FLOW_SENSOR_PIN 2

WaterFlowSensor waterFlowSensor(WATER_FLOW_SENSOR_PIN);
DS18B20 ds(3);
unsigned long lastCheckTime;
uint8_t dsSelected = 0;

void water_sensor_event();

void setup()
{
   Serial.begin(115200);

   waterFlowSensor.init();

   attachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR_PIN),
         water_sensor_event, RISING);

   lastCheckTime = millis();

   dsSelected = ds.selectNext();
   ds.setResolution(9);
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
      Serial.print(ds.getTempC());
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
