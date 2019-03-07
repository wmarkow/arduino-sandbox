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
   speakerMorseSender.setup();

   speakerMorseSender.setMessage(F("sos "));
   speakerMorseSender.startSending();
}

void loop()
{
   localTelegraph.loop();

   speakerMorseSender.continueSending();
}
