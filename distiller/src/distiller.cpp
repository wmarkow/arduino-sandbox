#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "DistillerLogger.h"
#include "DistillerLogHandler.h"
#include "drivers/WaterFlowSensor.h"
#include "drivers/DS18B20.h"

// Hardware pin configuration
#define WATER_FLOW_SENSOR_PIN 21
#define THERMOMETER_COLD_WATER_PIN 22
#define THERMOMETER_HOT_WATER_PIN 23

// BLE server configuration
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define KEG_TEMP_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define HEAD_TEMP_CHARACTERISTIC_UUID "5f5fae58-da57-4b24-8a5c-260272e2e066"
#define WATER_INPUT_TEMP_CHARACTERISTIC_UUID "71c6e9dc-3ddb-4d7e-ab3e-83678d439e97"
#define WATER_OUTPUT_TEMP_CHARACTERISTIC_UUID "8129dfa3-8f14-45c3-851c-b17c15086e6d"
#define WATER_FLOW_CHARACTERISTIC_UUID "8c0cb23c-3d34-43b0-92cf-e7eba4220616"

BLECharacteristic *kegTempCharacteristic = NULL;
BLECharacteristic *headTempCharacteristic = NULL;
BLECharacteristic *waterInputTempCharacteristic = NULL;
BLECharacteristic *waterOutputTempCharacteristic = NULL;
BLECharacteristic *waterFlowCharacteristic = NULL;

void createKegTempCharacteristic(BLEService *pService);
void createHeadTempCharacteristic(BLEService *pService);
void createWaterInputTempCharacteristic(BLEService *pService);
void createWaterOutputTempCharacteristic(BLEService *pService);
void createWaterFlowCharacteristic(BLEService *pService);

// Logger configuration
DistillerLogHandler logHandler(&Serial);

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

    RF24LOGGER_info(vendorId,
            "Distiller waiting 1000ms for power supply to settle down...");
    delay(1000);
    RF24LOGGER_info(vendorId, "Setup hardware...");

    waterFlowSensor.init();

    attachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR_PIN),
            water_sensor_event, RISING);

    lastCheckTime = millis();

    thermometerColdWater.begin();
    thermometerHotWater.begin();

    RF24LOGGER_info(vendorId, "Setup BLE server...");
    BLEDevice::init("Environment measurements"); // can not use polish specific characters
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);

    createKegTempCharacteristic(pService);
    createHeadTempCharacteristic(pService);
    createWaterInputTempCharacteristic(pService);
    createWaterOutputTempCharacteristic(pService);
    createWaterFlowCharacteristic(pService);

    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    BLEAdvertisementData advertisementData;
    advertisementData.setManufacturerData("wmarkow");
    pAdvertising->setAdvertisementData(advertisementData);
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    RF24LOGGER_info(vendorId,
            "BLE server created! Now you can read it in your phone!");

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
        float waterRpm = waterFlowSensor.getRpm();
        info.concat(waterRpm);
        info.concat(" ; ");
        waterFlowCharacteristic->setValue(waterRpm);

        // display cold water temperature
        float coldWaterTemp;
        if (thermometerColdWater.readTempC(&coldWaterTemp) == DS18B20_RESULT_OK)
        {
            info.concat(coldWaterTemp);

            waterInputTempCharacteristic->setValue(coldWaterTemp);
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

            waterOutputTempCharacteristic->setValue(hotWaterTemp);
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

void createKegTempCharacteristic(BLEService *pService)
{
    kegTempCharacteristic = pService->createCharacteristic(
    KEG_TEMP_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

    float value = 0;
    kegTempCharacteristic->setValue(value);
}

void createHeadTempCharacteristic(BLEService *pService)
{
    headTempCharacteristic = pService->createCharacteristic(
    HEAD_TEMP_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

    float value = 0;
    kegTempCharacteristic->setValue(value);
}

void createWaterInputTempCharacteristic(BLEService *pService)
{
    waterInputTempCharacteristic = pService->createCharacteristic(
    WATER_INPUT_TEMP_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

    float value = 0;
    kegTempCharacteristic->setValue(value);
}

void createWaterOutputTempCharacteristic(BLEService *pService)
{
    waterOutputTempCharacteristic = pService->createCharacteristic(
    WATER_OUTPUT_TEMP_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

    float value = 0;
    kegTempCharacteristic->setValue(value);
}

void createWaterFlowCharacteristic(BLEService *pService)
{
    waterFlowCharacteristic = pService->createCharacteristic(
    WATER_FLOW_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

    float value = 0;
    kegTempCharacteristic->setValue(value);
}
