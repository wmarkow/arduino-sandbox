#include <Arduino.h>
#include <FixedSizeArray.h>
#include "TSMP58000.h"
#include "brio/BrioDecoder.h"

TSMP58000 tsmp;
FixedSizeArray<IRData, 64> list = FixedSizeArray<IRData, 64>();
BrioDecoder brioDecoder;

void setup()
{
   Serial.begin(9600);
   delay(2000);
}

void loop()
{
   Serial.print(F("Waiting 3 sec for user click..."));
   if (tsmp.read(&list))
   {
      Serial.println(F(""));
      BrioMessage brioMessage;
      if (brioDecoder.decode(&list, &brioMessage))
      {
         brio_message_dump(&brioMessage);
      }
      else
      {
         tsmp.dump(&list);
      }
   }
   else
   {
      Serial.println(F(" nothing received"));
   }
}
