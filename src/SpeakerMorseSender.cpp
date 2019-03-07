#include "SpeakerMorseSender.h"

void SpeakerMorseSender::setOn()
{
   tone(pin, frequency);
}
void SpeakerMorseSender::setOff()
{
   if (carrFrequency == CARRIER_FREQUENCY_NONE)
   {
      noTone(pin);
   }
   else
   {
      tone(pin, carrFrequency);
   }
}
void SpeakerMorseSender::setReady()
{
   setOff();
}
void SpeakerMorseSender::setComplete()
{
   noTone(pin);
}
SpeakerMorseSender::SpeakerMorseSender(int outputPin,
      unsigned int toneFrequency, unsigned int carrierFrequency, float wpm) :
      MorseSender(outputPin, wpm), frequency(toneFrequency), carrFrequency(
            carrierFrequency)
{
}
;
