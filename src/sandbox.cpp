#include <Arduino.h>

#include <LCDKeypadShield.h>
#include "TelegraphKeyDecoder.h"
#include "MorseCodeTeacher.h"

LCDKeypadShield lcdKeypadShield(8, 9, 4, 5, 6, 7);
MorseCodeTeacher morseCodeTeacher(&lcdKeypadShield);

void setup()
{
   Serial.begin(9600);

   randomSeed(analogRead(1));

   lcdKeypadShield.begin(16, 2);
   lcdKeypadShield.print("hello world!");
   morseCodeTeacher.setup();
}

void loop()
{
   morseCodeTeacher.loop();
}
