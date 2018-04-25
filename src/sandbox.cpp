#include <Arduino.h>
#include "TSMP58000.h"

TSMP58000 tsmp;

void setup()
{
   Serial.begin(9600);
   delay(2000);
}

void loop()
{
   Serial.print(F("Waiting 3 sec for user click..."));
   if (tsmp.read())
   {
      Serial.println(F(""));
      tsmp.dump();
   }
   else
   {
      Serial.println(F(" nothing received"));
      tsmp.dump();
   }
}
