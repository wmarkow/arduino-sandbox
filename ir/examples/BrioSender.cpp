/*
 * BrioSender.cpp
 *
 *  Created on: 20.05.2018
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include <FixedSizeArray.h>
#include "../src/brio/BrioDecoder.h"

#include <IRremote.h>

FixedSizeArray<IRData, 64> list = FixedSizeArray<IRData, 64>();
BrioDecoder brioDecoder;

IRsend irSend;

void setup()
{
   Serial.begin(9600);
   delay(2000);
}

void sendCommand(BrioMessage* message);

void loop()
{
   if (Serial.available())
   {

      char c = Serial.read();

      uint8_t command = 0;
      if (c >= '0' && c <= '9')
      {
         command = c - 48; // from the ASCII table
      }
      else if (c >= 'a' && c <= 'f')
      {
         command = c - 97 + 10; // from the ASCII table
      }
      else
      {
         Serial.println(F("Invalid command!"));

         return;
      }

      Serial.print(F("Sending to channel A BRIO command: "));
      Serial.println(command);

      BrioMessage message;
      message.channel = BRIO_CHANNEL_A;
      message.command = command;

      sendCommand(&message);
//      sendCommand(&message);
   }
}

void sendCommand(BrioMessage* message)
{
   brioDecoder.encode(message, &list);

   irSend.enableIROut(38);
   for (uint8_t q = 0; q < list.getSize(); q++)
   {
      IRData* irData = list.peek(q);
      switch (irData->type)
      {
         case IR_TYPE_TOGGLE:
            irSend.mark(irData->duration);
            break;
         default:
            irSend.space(irData->duration);
      }
   }
}

