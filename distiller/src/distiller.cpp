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
#define THERMOMETER_COLD_WATER_PIN 22
#define THERMOMETER_HOT_WATER_PIN 23

WaterFlowSensor waterFlowSensor(WATER_FLOW_SENSOR_PIN);
DS18B20 thermometerColdWater(THERMOMETER_COLD_WATER_PIN);
DS18B20 thermometerHotWater(THERMOMETER_HOT_WATER_PIN);

unsigned long lastCheckTime;

void water_sensor_event();

void setup()
{
    Serial.begin(115200);

    waterFlowSensor.init();

    attachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR_PIN),
            water_sensor_event, RISING);

    lastCheckTime = millis();

    thermometerColdWater.begin();
    thermometerHotWater.begin();
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

        // display cold water temperature
        float coldWaterTemp;
        if (thermometerColdWater.readTempC(&coldWaterTemp) == DS18B20_RESULT_OK)
        {
            Serial.print(coldWaterTemp);
        }
        else
        {
            Serial.print("ERR");
        }
        Serial.print(" ; ");

        // display hot water temperature
        float hotWaterTemp;
        if (thermometerHotWater.readTempC(&hotWaterTemp) == DS18B20_RESULT_OK)
        {
            Serial.print(hotWaterTemp);
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
