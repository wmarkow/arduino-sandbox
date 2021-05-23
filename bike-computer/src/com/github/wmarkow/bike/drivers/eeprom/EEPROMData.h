/*
 * DashData.h
 *
 *  Created on: 22 maj 2021
 *      Author: wmarkowski
 */

#ifndef COM_GITHUB_WMARKOW_BIKE_DRIVERS_EEPROM_EEPROMDATA_H_
#define COM_GITHUB_WMARKOW_BIKE_DRIVERS_EEPROM_EEPROMDATA_H_

#include <stdint.h>

struct __attribute__((packed)) EEPROMHeaderData
{
    uint16_t crc;
    uint8_t lengthWithoutCrc;
    uint8_t version;
    uint32_t writeCycle;

    EEPROMHeaderData()
    {
        crc = 0;
        lengthWithoutCrc = 0;
        version = 0;
        writeCycle = 0;
    }
};

struct __attribute__((packed)) EEPROMData_V1 : public EEPROMHeaderData
{
    uint32_t totalDistanceInM;

    EEPROMData_V1() : EEPROMHeaderData()
    {
        version = 1;
        lengthWithoutCrc = 10;
        totalDistanceInM = 0;
    }
};

struct __attribute__((packed)) EEPROMData : public EEPROMData_V1
{
    EEPROMData() :
            EEPROMData_V1()
    {

    }
    ;
};

#endif /* COM_GITHUB_WMARKOW_BIKE_DRIVERS_EEPROM_EEPROMDATA_H_ */
