#include <Arduino.h>
#include "WaterFlowSensor.h"

WaterFlowSensor::WaterFlowSensor(uint8_t pin)
{
   this->pin = pin;
   this->waterSensorCounter = 0;
   this->waterSensorMeasureBeginMillis = millis();
   this->rpm = 0;
}

void WaterFlowSensor::init()
{
   pinMode(pin, INPUT);
   digitalWrite(pin, HIGH);

   waterSensorCounter = 0;
   waterSensorMeasureBeginMillis = millis();
   rpm = 0;
}

void WaterFlowSensor::loop()
{
   unsigned long measureSpanMillis = millis() - waterSensorMeasureBeginMillis;

   if (measureSpanMillis >= 1000L)
   {
      // calculate RPM
      uint16_t count = waterSensorCounter;
      rpm = 60000L * count / measureSpanMillis;

      waterSensorCounter = 0;
      waterSensorMeasureBeginMillis = millis();
   }
}

void WaterFlowSensor::tick()
{
   waterSensorCounter++;
}

double WaterFlowSensor::getRpm()
{
   return rpm;
}

