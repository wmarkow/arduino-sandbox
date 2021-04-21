#include <Arduino.h>

#include "DistillerLogger.h"
#include "DistillerLogHandler.h"
#include "drivers/WaterFlowSensor.h"
#include "drivers/DS18B20.h"

/*** Configure logger ***/
DistillerLogHandler logHandler(&Serial);

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
    rf24Logger.setHandler(&logHandler);

    RF24LOGGER_info(vendorId, "Distiller startup procedure...");

    RF24LOGGER_info(vendorId, "Distiller waiting 1000ms for power supply to settle down...");
    delay(1000);

    waterFlowSensor.init();

    attachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR_PIN),
            water_sensor_event, RISING);

    lastCheckTime = millis();

    thermometerColdWater.begin();
    thermometerHotWater.begin();

    RF24LOGGER_info(vendorId, "Distiller startup procedure end");
}

void loop()
{
    waterFlowSensor.loop();

    unsigned long measureSpanMillis = millis() - lastCheckTime;

    if (measureSpanMillis >= 1000L)
    {
        String info = "";

        // display water flow
        info.concat(waterFlowSensor.getRpm());
        info.concat(" ; ");

        // display cold water temperature
        float coldWaterTemp;
        if (thermometerColdWater.readTempC(&coldWaterTemp) == DS18B20_RESULT_OK)
        {
            info.concat(coldWaterTemp);
        }
        else
        {
            info.concat("ERR");
        }
        info.concat(" ; ");

        // display hot water temperature
        float hotWaterTemp;
        if (thermometerHotWater.readTempC(&hotWaterTemp) == DS18B20_RESULT_OK)
        {
            info.concat(hotWaterTemp);
        }
        else
        {
            info.concat("ERR");
        }
        info.concat(" ; ");

        // display time span
        info.concat(measureSpanMillis);
        lastCheckTime = millis();

        RF24LOGGER_info(vendorId, info.c_str());
    }
}

void water_sensor_event()
{
    waterFlowSensor.tick();
}
