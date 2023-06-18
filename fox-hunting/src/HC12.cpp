/*
 * HC12.cpp
 *
 *  Created on: 27.06.2018
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "HC12.h"

HC12::HC12() :
      softwareSerial(HC12_TXD_UNO_RX_PIN, HC12_RXD_UNO_TX_PIN)
{
}

void HC12::begin()
{
   // Because Arduino may be restarted while HC-12 being still powered up,
   // it may happen that HC-12 is already configured to communicate with
   // Arduino with a different (than default 9600bps) speed. It is here
   // important to set software serial to the correct speed.
   
   // Try first with default speed...
   softwareSerial.begin(HC12_DEFAULT_BAUDRATE);
   if(isChipConnected())
   {
      return;
   }

   // ... then try with lowered speed
   softwareSerial.begin(HC12_BAUDRATE);
   
   enterTransparentMode();
}

bool HC12::isChipConnected()
{
   enterCommandMode();
   softwareSerial.print(F("AT"));
   String response = getCommandResponse();
   enterTransparentMode();

   if (response.equals(F("OK")))
   {
      return true;
   }

   Serial.println(response);
   return false;
}

int8_t HC12::getTransmitterPowerInDbm()
{
   enterCommandMode();
   softwareSerial.print(F("AT+RP"));
   String response = getCommandResponse();
   enterTransparentMode();

   if (!response.startsWith(F("OK+RP:")))
   {
      return -99;
   }

   String valueAsString = response.substring(6, response.indexOf(F("dBm")));
   return valueAsString.toInt();
}

uint16_t HC12::getAirDataRateInKbs()
{
   enterCommandMode();
   softwareSerial.print(F("AT+RB"));
   String response = getCommandResponse();
   enterTransparentMode();

   if (!response.startsWith(F("OK+B")))
   {
      return 0;
   }

   String valueAsString = response.substring(4);
   long int uartBaudRate = valueAsString.toInt();
   if (uartBaudRate <= 2400)
   {
      return 5;
   }
   if (uartBaudRate <= 9600)
   {
      return 15;
   }
   if (uartBaudRate <= 38400)
   {
      return 58;
   }

   return 236;
}

uint8_t HC12::switchSerialPortTo2400bps()
{
   enterCommandMode();
   softwareSerial.print(F("AT+B2400"));
   String response = getCommandResponse();
   enterTransparentMode();

   if (!response.startsWith(F("OK+B")))
   {
      return 1;
   }

   softwareSerial.begin(HC12_BAUDRATE);

   return 0;
}

uint8_t HC12::setTxPowerValue(uint8_t value)
{
   enterCommandMode();
   softwareSerial.print(F("AT+P1"));
   String response = getCommandResponse();
   enterTransparentMode();

   if (!response.startsWith(F("OK+P")))
   {
      return 1;
   }

   return 0;
}

uint8_t HC12::getRFChannel()
{
   enterCommandMode();
   softwareSerial.print(F("AT+RC"));
   String response = getCommandResponse();
   enterTransparentMode();

   if (!response.startsWith(F("OK+RC")))
   {
      return 0;
   }

   String valueAsString = response.substring(5);
   return valueAsString.toInt();
}

bool HC12::write(uint8_t* data, uint8_t size)
{
   softwareSerial.write((char*) data, size);
}

uint8_t HC12::available()
{
   return softwareSerial.available();
}

int HC12::read(uint8_t *buffer, size_t length)
{
   return softwareSerial.readBytes(buffer, length);
}

int HC12::read()
{
   return softwareSerial.read();
}

int HC12::write(uint8_t data)
{
   return softwareSerial.write(data);
}

void HC12::enterTransparentMode()
{
   pinMode(HC12_SET_PIN, OUTPUT);
   digitalWrite(HC12_SET_PIN, HIGH);

   delay(50);
}

void HC12::enterCommandMode()
{
   pinMode(HC12_SET_PIN, OUTPUT);
   digitalWrite(HC12_SET_PIN, LOW);

   delay(50);
}

String HC12::getCommandResponse()
{
   unsigned long time = millis();
   String resultString = "";

   while (millis() - time < 200)
   {
      if (softwareSerial.available())
      {
         char character = softwareSerial.read();

         if (character == '\n')
         {
            break;
         }

         if (character != '\r')
         {
            resultString += character;
         }

      }
   }

   return resultString;
}
