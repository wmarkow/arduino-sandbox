#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "DistillerLogger.h"
#include "DistillerLogHandler.h"
#include "drivers/WaterFlowSensor.h"
#include "drivers/DS18B20.h"
#include "DistillerData.h"

// Hardware pin configuration
// Case side view:
//
// CW   USB   BOIL
//  HW       HEAD
//
#define THERMOMETER_COLD_WATER_PIN 22
#define THERMOMETER_HOT_WATER_PIN 23
#define THERMOMETER_BOILER_PIN 21
#define THERMOMETER_HEADER_PIN 19
#define WATER_FLOW_SENSOR_PIN 18


// BLE server configuration
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define DISTILLER_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic *distillerCharacteristic = NULL;

void createDistillerCharacteristic(BLEService *pService);

// Logger configuration
DistillerLogHandler logHandler(&Serial);

WaterFlowSensor waterFlowSensor(WATER_FLOW_SENSOR_PIN);
DS18B20 thermometerColdWater(THERMOMETER_COLD_WATER_PIN);
DS18B20 thermometerHotWater(THERMOMETER_HOT_WATER_PIN);
DS18B20 thermometerBoiler(THERMOMETER_BOILER_PIN);
DS18B20 thermometerHeader(THERMOMETER_HEADER_PIN);

unsigned long lastCheckTime;

void water_sensor_event();

void setup()
{
    Serial.begin(115200);
    rf24Logging.setHandler(&logHandler);

    RF24Log_info(vendorId, "Distiller startup procedure...");

    RF24Log_info(vendorId,
            "Distiller waiting 1000ms for power supply to settle down...");
    delay(1000);
    RF24Log_info(vendorId, "Setup hardware...");

    waterFlowSensor.init();

    attachInterrupt(digitalPinToInterrupt(WATER_FLOW_SENSOR_PIN),
            water_sensor_event, RISING);

    lastCheckTime = millis();

    thermometerColdWater.setResolution(10);
    thermometerColdWater.begin();

    thermometerHotWater.setResolution(10);
    thermometerHotWater.begin();

    thermometerBoiler.setResolution(11);
    thermometerBoiler.begin();

    thermometerHeader.setResolution(12);
    thermometerHeader.begin();

    RF24Log_info(vendorId, "Setup BLE server...");
    BLEDevice::init("Environment measurements"); // can not use polish specific characters
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);

    createDistillerCharacteristic(pService);

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
    RF24Log_info(vendorId,
            "BLE server created! Now you can read it in your phone!");
    Serial.println(sizeof(unsigned long));
    RF24Log_info(vendorId, "Distiller startup procedure end");
}

void loop()
{
    waterFlowSensor.loop();

    unsigned long measureSpanMillis = millis() - lastCheckTime;

    if (measureSpanMillis >= 1000L)
    {
        DistillerData distillerData;
        String info = "";

        // add current timestamp
        distillerData.systemUpTime = millis();
        // display water flow
        float waterRpm = waterFlowSensor.getRpm();
        info.concat(waterRpm);
        info.concat(" ; ");
        distillerData.waterRpm = waterRpm;

        // display cold water temperature
        float coldWaterTemp;
        if (thermometerColdWater.readTempC(&coldWaterTemp) == DS18B20_RESULT_OK)
        {
            info.concat(coldWaterTemp);
            distillerData.coldWaterTemp = coldWaterTemp;
        }
        else
        {
            info.concat("ERR");
            distillerData.coldWaterTemp = DISTILLER_INVALID_TEMP;
        }
        info.concat(" ; ");

        // display hot water temperature
        float hotWaterTemp;
        if (thermometerHotWater.readTempC(&hotWaterTemp) == DS18B20_RESULT_OK)
        {
            info.concat(hotWaterTemp);
            distillerData.hotWaterTemp = hotWaterTemp;
        }
        else
        {
            info.concat("ERR");
            distillerData.hotWaterTemp = DISTILLER_INVALID_TEMP;
        }
        info.concat(" ; ");

        // display boiler temperature
        float boilerTemp;
        if (thermometerBoiler.readTempC(&boilerTemp) == DS18B20_RESULT_OK)
        {
            info.concat(hotWaterTemp);
            distillerData.kegTemp = boilerTemp;
        }
        else
        {
            info.concat("ERR");
            distillerData.kegTemp = DISTILLER_INVALID_TEMP;
        }
        info.concat(" ; ");

        // display header temperature
        float headerTemp;
        if (thermometerHeader.readTempC(&headerTemp) == DS18B20_RESULT_OK)
        {
            info.concat(headerTemp);
            distillerData.headerTemp = headerTemp;
        }
        else
        {
            info.concat("ERR");
            distillerData.headerTemp = DISTILLER_INVALID_TEMP;
        }
        info.concat(" ; ");

        // display time span
        info.concat(measureSpanMillis);
        lastCheckTime = millis();

        RF24Log_info(vendorId, info.c_str());

        distillerCharacteristic->setValue(distillerData.getArray(), distillerData.getArraySize());
    }
}

void water_sensor_event()
{
    waterFlowSensor.tick();
}

void createDistillerCharacteristic(BLEService *pService)
{
    distillerCharacteristic = pService->createCharacteristic(
            DISTILLER_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

    float value = 0;
    distillerCharacteristic->setValue(value);
}
