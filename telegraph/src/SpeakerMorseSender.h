#ifndef SPEAKERMORSESENDER_H_
#define SPEAKERMORSESENDER_H_

#include "MorseCodeSequencer.h"

class SpeakerMorseSender : public MorseCodeSequencer
{
private:
   uint8_t outputPin;
protected:
   void onDotStart();
   void onDashStart();
   void onDotStop();
   void onDashStop();
public:
   SpeakerMorseSender(int outputPin);
   void setup();
};

#endif /* SPEAKERMORSESENDER_H_ */
