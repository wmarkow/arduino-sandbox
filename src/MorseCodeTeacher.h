#ifndef MORSECODETEACHER_H_
#define MORSECODETEACHER_H_

#include <Arduino.h>
#include <LCDKeypadShield.h>
#include "SpeakerMorseSender.h"

class MorseCodeTeacher
{
private:
   LCDKeypadShield *lcdKeypadShield;
   SpeakerMorseSender speakerMorseSender;
   uint8_t state;

   void display(char c);
public:
   MorseCodeTeacher(LCDKeypadShield *lcdKeypadShield);
   void setup();
   void loop();
};

#endif /* MORSECODETEACHER_H_ */
