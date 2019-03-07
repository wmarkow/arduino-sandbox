#ifndef SPEAKERMORSESENDER_H_
#define SPEAKERMORSESENDER_H_

#include "MorseSender.h"

class SpeakerMorseSender : public MorseSender
{
private:
   unsigned int frequency;
   unsigned int carrFrequency;
protected:
   virtual void setOn();
   virtual void setOff();
   virtual void setReady();
   virtual void setComplete();
public:
   // concert A = 440
   // middle C = 261.626; higher octaves = 523.251, 1046.502
   SpeakerMorseSender(int outputPin, unsigned int toneFrequency = 1046,
         unsigned int carrierFrequency = CARRIER_FREQUENCY_NONE, float wpm =
               WPM_DEFAULT);
};

#endif /* SPEAKERMORSESENDER_H_ */
