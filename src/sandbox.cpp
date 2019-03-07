#include <Arduino.h>
#include "LocalTelegraph.h"

LocalTelegraph localTelegraph;

void setup()
{
   Serial.begin(9600);

   localTelegraph.init();
}

void loop()
{
   localTelegraph.loop();
}
