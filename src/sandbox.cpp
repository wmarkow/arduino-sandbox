#include <Arduino.h>

#include <LCDKeypadShield.h>
#include "LocalTelegraph.h"
#include "MorseCodeTeacher.h"

LocalTelegraph localTelegraph;
LCDKeypadShield lcdKeypadShield(8, 9, 4, 5, 6, 7);
MorseCodeTeacher morseCodeTeacher(&lcdKeypadShield);

void setup()
{
   Serial.begin(9600);

   randomSeed(analogRead(1));

   localTelegraph.init();

   lcdKeypadShield.begin(16, 2);
   lcdKeypadShield.print("hello world!");
   morseCodeTeacher.setup();
}

void loop()
{
   localTelegraph.loop();
   morseCodeTeacher.loop();
}
