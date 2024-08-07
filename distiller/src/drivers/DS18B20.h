#ifndef SRC_DRIVERS_DS18B20_H_
#define SRC_DRIVERS_DS18B20_H_

#include <OneWire.h>
#include <DallasTemperature.h>

#define DS18B20_RESULT_OK 0
#define DS18B20_RESULT_ERR 1


class DS18B20
{
public:
   DS18B20(uint8_t pin);
   void begin();
   uint8_t readTempC(float *value);

   /***
    *  Set resolution to 9, 10, 11, or 12 bits. Default resolution is 9 bits.
    */
   void setResolution(uint8_t resolution);

private:
   OneWire oneWireBus;
   DallasTemperature thermometerBus;
   bool reinit;
   uint8_t resolution;
};



#endif /* SRC_DRIVERS_DS18B20_H_ */
