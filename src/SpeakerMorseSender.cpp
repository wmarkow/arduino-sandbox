#include "SpeakerMorseSender.h"

#define DEFAULT_FREQUENCY 1000

SpeakerMorseSender::SpeakerMorseSender(int outputPin) :
      MorseCodeSequencer()
{
   this->outputPin = outputPin;
}

void SpeakerMorseSender::onDotStart()
{
   tone(outputPin, DEFAULT_FREQUENCY);
}

void SpeakerMorseSender::onDashStart()
{
   tone(outputPin, DEFAULT_FREQUENCY);
}

void SpeakerMorseSender::onDotStop()
{
   noTone(outputPin);
}

void SpeakerMorseSender::onDashStop()
{
   noTone(outputPin);
}

void SpeakerMorseSender::setup()
{
   pinMode(outputPin, OUTPUT);
}
