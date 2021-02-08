/*
 * distiller.cpp
 *
 *  Created on: 7 lut 2021
 *      Author: wmarkowski
 */

#include <Arduino.h>

#define WATER_FLOW_SENSOR_PIN 2

volatile uint16_t waterSensorCounter = 0;
unsigned long waterSensorMeasureBeginMillis;

void water_sensor_event();

void setup()
{
   Serial.begin(115200);

   waterSensorCounter = 0;
   waterSensorMeasureBeginMillis = millis();

   pinMode(WATER_FLOW_SENSOR_PIN, INPUT);
   digitalWrite(WATER_FLOW_SENSOR_PIN, HIGH);
   attachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR_PIN),
         water_sensor_event, RISING);
}

void loop()
{
   unsigned long measureSpanMillis = millis() - waterSensorMeasureBeginMillis;

   if (measureSpanMillis >= 1000L)
   {
      // calculate RPM
      uint16_t count = waterSensorCounter;
      double rpm = 60000L * count / measureSpanMillis;

      Serial.print("RPM: ");
      Serial.println(rpm);
      Serial.print("Pulses:");
      Serial.println(count);

      waterSensorCounter = 0;
      waterSensorMeasureBeginMillis = millis();
   }

}

void water_sensor_event()
{
   waterSensorCounter++;
}
