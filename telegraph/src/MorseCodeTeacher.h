#ifndef MORSECODETEACHER_H_
#define MORSECODETEACHER_H_

#include <Arduino.h>
#include <LCDKeypadShield.h>
#include "SpeakerMorseSender.h"
#include "TelegraphKeyDecoder.h"

class MorseCodeTeacher : public TelegraphKeyDecoderListener
{
private:
   LCDKeypadShield *lcdKeypadShield;
   SpeakerMorseSender speakerMorseSender;
   TelegraphKeyDecoder telegraphKeyDecoder;
   uint8_t state;
   char askedChar;

   void display(char c);
protected:
   void onCharDecoded(char c);
   void onError();
public:
   MorseCodeTeacher(LCDKeypadShield *lcdKeypadShield);
   void setup();
   void loop();
};

#endif /* MORSECODETEACHER_H_ */
