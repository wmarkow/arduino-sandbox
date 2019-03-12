#ifndef MORSECODESEQUENCER_H_
#define MORSECODESEQUENCER_H_

#include <Arduino.h>

#define    MCS_STATE_IDLE 0
#define MCS_STATE_SENDING 1
#define MCS_STATE_TRY_TO_SEND 2
#define MCS_STATE_WAITING_FOR_END 3
#define MCS_STATE_WAITING_FOR_PAUSE_END 4

typedef unsigned char MorseBitmask;

// Morse Code (explicit declaration of letter timings)
const MorseBitmask MORSE_LETTERS[26] =
{
/* a */B101,
/* b */B11000,
/* c */B11010,
/* d */B1100,
/* e */B10,
/* f */B10010,
/* g */B1110,
/* h */B10000,
/* i */B100,
/* j */B10111,
/* k */B1101,
/* l */B10100,
/* m */B111,
/* n */B110,
/* o */B1111,
/* p */B10110,
/* q */B11101,
/* r */B1010,
/* s */B1000,
/* t */B11,
/* u */B1001,
/* v */B10001,
/* w */B1011,
/* x */B11001,
/* y */B11011,
/* z */B11100, };

class MorseCodeSequencer
{
private:
   MorseBitmask morseBitmaskToSent;
   uint8_t state;
   uint8_t bitIndex;
   uint32_t lastSendTime;
   uint16_t dotDuration;
   uint16_t dashDuration;
public:
   MorseCodeSequencer();
   void loop();
   bool send(char c);
   void setWPM(uint8_t wpm);
   bool isBusy();
   MorseBitmask getMorseBitmask(char c);
   virtual void onDotStart() = 0;
   virtual void onDotStop() = 0;
   virtual void onDashStart() = 0;
   virtual void onDashStop() = 0;
};

#endif /* MORSECODESEQUENCER_H_ */
