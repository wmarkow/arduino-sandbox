#include "SpeakerMorseSender.h"

SpeakerMorseSender::SpeakerMorseSender(int outputPin) : MorseSequencer()
{
   this->outputPin = outputPin;
}

void SpeakerMorseSender::onDotStart()
{
   analogWrite(outputPin, 128);
   Serial.print(".");
}

void SpeakerMorseSender::onDashStart()
{
   analogWrite(outputPin, 128);
   Serial.print("-");
}

void SpeakerMorseSender::onDotStop()
{
   analogWrite(outputPin, 0);
}

void SpeakerMorseSender::onDashStop()
{
   analogWrite(outputPin, 0);
}

void SpeakerMorseSender::setup()
{
   pinMode(outputPin, OUTPUT);
}
