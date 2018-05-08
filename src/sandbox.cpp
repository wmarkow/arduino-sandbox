#include <Arduino.h>
#include <FixedSizeArray.h>
#include "TSMP58000.h"

TSMP58000 tsmp;
FixedSizeArray<IRData, 64> list = FixedSizeArray<IRData, 64>();

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
      tsmp.dump(&list);
   }
   else
   {
      Serial.println(F(" nothing received"));
   }
}
