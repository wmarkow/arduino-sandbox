/*
 * BrioMessage.cpp
 *
 *  Created on: 09.05.2018
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "BrioMessage.h"

void brio_message_dump(BrioMessage* brioMessage)
{
   switch (brioMessage->channel)
   {
      case BRIO_CHANNEL_A:
         Serial.print(F("channel A, "));
         break;
      case BRIO_CHANNEL_B:
         Serial.print(F("channel B, "));
         break;
      default:
         Serial.print(F("channel "));
         Serial.print(brioMessage->channel);
         Serial.print(F(", "));
   }

   switch (brioMessage->command)
   {
      case BRIO_COMMAND_FAST_FORWARD:
         Serial.println(F("cmd FFOR"));
         break;
      case BRIO_COMMAND_SLOW_FORWARD:
         Serial.println(F("cmd SFOR"));
         break;
      case BRIO_COMMAND_STOP:
         Serial.println(F("cmd STOP"));
         break;
      case BRIO_COMMAND_BACKWARD:
         Serial.println(F("cmd BACK"));
         break;
      case BRIO_COMMAND_TOGGLE_LIGHT:
         Serial.println(F("cmd T_LIGHT"));
         break;
      case BRIO_COMMAND_PLAY_SOUND:
         Serial.println(F("cmd SOUND"));
         break;
      default:
         Serial.print(F("cmd "));
         Serial.println(brioMessage->command);
   }
}
