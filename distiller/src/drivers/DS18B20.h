/*
 * DS18B20.h
 *
 *  Created on: 26 lut 2021
 *      Author: wmarkowski
 */

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
private:
   OneWire oneWireBus;
   DallasTemperature thermometerBus;
};



#endif /* SRC_DRIVERS_DS18B20_H_ */
