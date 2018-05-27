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

void loop()
{
   if (Serial.available())
   {

      char c = Serial.read();

      if (c == 'q')
      {
         Serial.println("Sending TOGGLEL to A.");

         BrioMessage message;
         message.channel = BRIO_CHANNEL_A;
         message.command = BRIO_COMMAND_TOGGLE_LIGHT;

         brioDecoder.encode(&message, &list);

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

   }
}

