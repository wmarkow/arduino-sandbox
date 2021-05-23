
#include <Arduino.h>
#include "EEPROMStorage.h"
#include <util/crc16.h>


void EEPROMStorage::read(EEPROMData* eepromData)
{
    EEPROMHeaderData header;

    // read data header from EEPROM
    EEPROM.get(0, header);

    // check CRC
    uint16_t calculatedCRC = calculateCRC(&header);
    if(calculatedCRC != header.crc)
    {
        // CRC mismatch
        // return immediately and do nothing with the passed EEPROMData
        // It is assumed that passed EEPROMData contain a default initial values
        Serial.println(F("CRC mismatch while reading from EEPROM!"));

        return;
    }

    readData(&header, eepromData);
}


uint16_t EEPROMStorage::calculateCRC(EEPROMHeaderData* header)
{
    uint16_t crc = 0;
    // the lengthWithoutCrc variable begins at byte index 2 in EEPROM
    uint16_t eepromStartIndex = 2;
    uint16_t eepromEndIndex = eepromStartIndex + header->lengthWithoutCrc;

    for(uint16_t index = eepromStartIndex ; index < eepromEndIndex ; index ++)
    {
        crc = _crc16_update(crc, EEPROM[index]);
    }

    return crc;
}

void EEPROMStorage::readData(EEPROMHeaderData* eepromData, EEPROMData* dst)
{
    if(eepromData->version == dst->version)
    {
        // no data migration needed
        EEPROM.get(0, dst);

        return;
    }

    Serial.println(F("EEPROM data migration not implemented!"));
}
