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
      thermometerBus.getAddress(this->deviceAddress, 0);

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
   if (thermometerBus.getDeviceCount() == 0)
   {
      return DS18B20_RESULT_ERR;
   }

   if (thermometerBus.readPowerSupply(deviceAddress) == true)
   {
      // Parasite mode (when Vdd is connected to the ground) is considered by the project to be not supported.
      // It has been noticed that parasite mode is mostly also detected (not in 100% cases) when Vdd pin is left
      // unconnected; this helps to improve the hardware failure handling.
      return DS18B20_RESULT_ERR;
   }

   thermometerBus.requestTemperatures();
   float temp = thermometerBus.getTempCByIndex(0);

   if (temp == DEVICE_DISCONNECTED_C)
   {
      return DS18B20_RESULT_ERR;
   }

   *value = temp;

   return DS18B20_RESULT_OK;
}
