#include "../DistillerLogger.h"
#include "DS18B20.h"

DS18B20::DS18B20(uint8_t pin) :
        oneWireBus(pin), thermometerBus(&oneWireBus)
{
    this->reinit = false;
}

void DS18B20::begin()
{
    thermometerBus.begin();
    thermometerBus.setWaitForConversion(true);

    if (thermometerBus.getDeviceCount() == 1)
    {
        RF24Log_info(vendorId, "DS18B20 thermometer found");

        thermometerBus.setResolution(11);
    }
    else
    {
        RF24Log_info(vendorId, "DS18B20 thermometer NOT found!");
    }

    reinit = false;
}

uint8_t DS18B20::readTempC(float *value)
{
    if(reinit)
    {
        begin();
    }

    if (thermometerBus.getDeviceCount() == 0)
    {
        reinit = true;

        return DS18B20_RESULT_ERR;
    }

    if (thermometerBus.readPowerSupply(NULL) == true)
    {
        // Parasite mode (when Vdd is connected to the ground) is considered by the project to be not supported.
        // It has been noticed that parasite mode is mostly also detected (not in 100% cases) when Vdd pin is left
        // unconnected; this helps to improve the hardware failure handling.
        reinit = true;

        return DS18B20_RESULT_ERR;
    }

    thermometerBus.requestTemperatures();
    float temp = thermometerBus.getTempCByIndex(0);

    if (temp == DEVICE_DISCONNECTED_C)
    {
        reinit = true;

        return DS18B20_RESULT_ERR;
    }

    *value = temp;

    return DS18B20_RESULT_OK;
}
