/*
 Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
 Ported to Arduino ESP32 by Evandro Copercini
 updates by chegewara
 */
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define KEG_TEMP_CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define HEAD_TEMP_CHARACTERISTIC_UUID "5f5fae58-da57-4b24-8a5c-260272e2e066"
#define WATER_INPUT_TEMP_CHARACTERISTIC_UUID "71c6e9dc-3ddb-4d7e-ab3e-83678d439e97"
#define WATER_OUTPUT_TEMP_CHARACTERISTIC_UUID "8129dfa3-8f14-45c3-851c-b17c15086e6d"
#define WATER_FLOW_CHARACTERISTIC_UUID "8c0cb23c-3d34-43b0-92cf-e7eba4220616"

float kegTemp = 82.12;
float headTemp = 78.12;
float waterInputTemp = 20.01;
float waterOutputTemp = 70.1;
float waterFlow = 18.2;

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

void setup() {
	Serial.begin(57600);
	Serial.println("Starting BLE work!");

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
	pAdvertising->addServiceUUID(SERVICE_UUID);
	pAdvertising->setScanResponse(true);
	pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
	pAdvertising->setMinPreferred(0x12);
	BLEDevice::startAdvertising();
	Serial.println(
			"Characteristic defined! Now you can read it in your phone!");
}

void loop() {
	// put your main code here, to run repeatedly:
	delay(2000);
	Serial.println("loop");
}

void createKegTempCharacteristic(BLEService *pService) {
	kegTempCharacteristic = pService->createCharacteristic(
	KEG_TEMP_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

	kegTempCharacteristic->setValue(kegTemp);
}

void createHeadTempCharacteristic(BLEService *pService) {
	headTempCharacteristic = pService->createCharacteristic(
	HEAD_TEMP_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

	headTempCharacteristic->setValue(headTemp);
}

void createWaterInputTempCharacteristic(BLEService *pService) {
	waterInputTempCharacteristic = pService->createCharacteristic(
	WATER_INPUT_TEMP_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

	waterInputTempCharacteristic->setValue(waterInputTemp);
}

void createWaterOutputTempCharacteristic(BLEService *pService) {
	waterOutputTempCharacteristic = pService->createCharacteristic(
	WATER_OUTPUT_TEMP_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

	waterOutputTempCharacteristic->setValue(waterOutputTemp);
}

void createWaterFlowCharacteristic(BLEService *pService) {
	waterFlowCharacteristic = pService->createCharacteristic(
	WATER_FLOW_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ);

	waterFlowCharacteristic->setValue(waterFlow);
}

