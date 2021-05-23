/*
 * EepromStorage.h
 *
 *  Created on: 23 maj 2021
 *      Author: wmarkowski
 */

#ifndef COM_GITHUB_WMARKOW_BIKE_DRIVERS_EEPROM_EEPROMSTORAGE_H_
#define COM_GITHUB_WMARKOW_BIKE_DRIVERS_EEPROM_EEPROMSTORAGE_H_

#include <EEPROM.h>
#include <com/github/wmarkow/bike/drivers/eeprom/EEPROMData.h>

class EEPROMStorage
{
public:
    void read(EEPROMData* eepromData);
    void write(EEPROMData* eepromData);

private:
    uint16_t calculateCRCInEEPROM(EEPROMHeaderData* header);
    uint16_t calculateCRC(EEPROMData* eepromData);
    void readData(EEPROMHeaderData* eepromData, EEPROMData* dst);
};



#endif /* COM_GITHUB_WMARKOW_BIKE_DRIVERS_EEPROM_EEPROMSTORAGE_H_ */
