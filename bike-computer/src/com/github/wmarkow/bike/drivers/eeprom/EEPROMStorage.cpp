#include <Arduino.h>
#include "EEPROMStorage.h"
#include <util/crc16.h>

void EEPROMStorage::read(EEPROMData *eepromData)
{
    EEPROMHeaderData header;

    // read data header from EEPROM
    EEPROM.get(0, header);

    // check CRC
    uint16_t calculatedCRC = calculateCRCInEEPROM(&header);
    if (calculatedCRC != header.crc)
    {
        // CRC mismatch
        // return immediately and do nothing with the passed EEPROMData
        // It is assumed that passed EEPROMData contain a default initial values
        Serial.println(F("CRC mismatch while reading from EEPROM!"));

        return;
    }

    Serial.println(F("EEPROM CRC matches. Data will be read from EEPROM."));
    readData(&header, eepromData);
}

void EEPROMStorage::write(EEPROMData *eepromData)
{
    Serial.print(F("Writing data to EEPROM: "));

    eepromData->writeCycle++;
    eepromData->crc = calculateCRC(eepromData);

    uint8_t *ptr = (uint8_t*) eepromData;
    for (uint8_t q = 0; q < sizeof(EEPROMData); q++)
    {
        uint8_t data = *ptr;
        EEPROM.write(q, data);
        Serial.print(data, HEX);
        Serial.print(" ");
        ptr++;
    }
    Serial.println();
}

uint16_t EEPROMStorage::calculateCRCInEEPROM(EEPROMHeaderData *header)
{
    uint16_t crc = 0;

    // the lengthWithoutCrc variable begins at byte index 2 in EEPROM
    uint8_t index = 2;
    for (uint16_t q = 0; q < header->lengthWithoutCrc; q++)
    {
        uint8_t data = EEPROM[index];
        crc = _crc16_update(crc, data);
        index++;
    }

    return crc;
}

uint16_t EEPROMStorage::calculateCRC(EEPROMData *data)
{
    uint16_t crc = 0;

    uint8_t *ptr = (uint8_t*) data;
    // the lengthWithoutCrc variable begins at byte index 2 in EEPROM
    ptr++;
    ptr++;
    for (uint16_t q = 0; q < data->lengthWithoutCrc; q++)
    {
        crc = _crc16_update(crc, *ptr);
        ptr++;
    }

    return crc;
}

void EEPROMStorage::readData(EEPROMHeaderData *eepromData, EEPROMData *dst)
{
    Serial.print(F("Reading data from EEPROM: "));

    if (eepromData->version == dst->version)
    {
        // no data migration needed

        uint8_t *ptr = (uint8_t*) dst;
        for (uint8_t q = 0; q < sizeof(EEPROMData); q++)
        {
            *ptr = EEPROM[q];
            Serial.print(*ptr, HEX);
            Serial.print(" ");
            ptr++;
        }
        Serial.println(" ");

        return;
    }

    Serial.println(F("EEPROM data migration not implemented!"));
}
