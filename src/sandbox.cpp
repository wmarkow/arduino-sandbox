#include <Arduino.h>

#include "LocalTelegraph.h"
#include "SpeakerMorseSender.h"

#define BUZZER_PIN 3

LocalTelegraph localTelegraph;
SpeakerMorseSender speakerMorseSender(BUZZER_PIN);

void setup()
{
   Serial.begin(9600);

   localTelegraph.init();
}

void loop()
{
   localTelegraph.loop();

   if(speakerMorseSender.isBusy() == false)
   {
      delay(500);
      speakerMorseSender.send('s');
   }
   speakerMorseSender.loop();
}
