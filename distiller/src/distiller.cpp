/*
 * distiller.cpp
 *
 *  Created on: 7 lut 2021
 *      Author: wmarkowski
 */

#include <Arduino.h>

#include "drivers/WaterFlowSensor.h"
#include "drivers/DS18B20.h"

#define WATER_FLOW_SENSOR_PIN 2
#define TERMOMETER_COLD_WATER_PIN 22

WaterFlowSensor waterFlowSensor(WATER_FLOW_SENSOR_PIN);
DS18B20 thermometer(TERMOMETER_COLD_WATER_PIN);

unsigned long lastCheckTime;

void water_sensor_event();

void setup()
{
    Serial.begin(115200);

    waterFlowSensor.init();

    attachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR_PIN),
            water_sensor_event, RISING);

    lastCheckTime = millis();

    thermometer.begin();
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
        float temp;
        if (thermometer.readTempC(&temp) == DS18B20_RESULT_OK)
        {
            Serial.print(temp);
        }
        else
        {
            Serial.print("ERR");
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
