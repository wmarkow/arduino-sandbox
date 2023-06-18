/*
 * HC12.h
 *
 *  Created on: 27.06.2018
 *      Author: wmarkowski
 */

#ifndef MESH_LINK_HC12_H_
#define MESH_LINK_HC12_H_

#include <SoftwareSerial.h>

#define HC12_TXD_UNO_RX_PIN 8
#define HC12_RXD_UNO_TX_PIN 7
#define HC12_SET_PIN 6

#define HC12_DEFAULT_BAUDRATE 9600
#define HC12_BAUDRATE 2400

class HC12
{
private:
   SoftwareSerial softwareSerial;
   void enterTransparentMode();
   void enterCommandMode();
   String getCommandResponse();
public:
   HC12();
   void begin();
   bool isChipConnected();
   int8_t getTransmitterPowerInDbm();
   uint16_t getAirDataRateInKbs();
   uint8_t switchSerialPortTo2400bps();
   uint8_t setTxPowerValue(uint8_t value);
   uint8_t getRFChannel();
   bool write(uint8_t *data, uint8_t size);
   int read(uint8_t *buffer, size_t length);
   int read();
   int write(uint8_t data);
   uint8_t available();
};


#endif /* MESH_LINK_HC12_H_ */
