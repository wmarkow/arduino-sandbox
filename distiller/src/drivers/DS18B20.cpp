/*
 * DS18B20.cpp
 *
 *  Created on: 26 lut 2021
 *      Author: wmarkowski
 */
#include "DS18B20.h"

DS18B20::DS18B20(uint8_t pin) :
      oneWireBus(pin), thermometerBus(&oneWireBus)
{

}

void DS18B20::begin()
{
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

uint8_t DS18B20::readTempC(float *value)
{
   thermometerBus.requestTemperatures();
   float temp = thermometerBus.getTempCByIndex(0);

   if (temp == DEVICE_DISCONNECTED_C)
   {
      return DS18B20_RESULT_ERR;
   }

   *value = temp;

   return DS18B20_RESULT_OK;
}
