#include "MorseCodeSequencer.h"

#define WPM_DEFAULT  12
// PARIS WPM measurement: 50; CODEX WPM measurement: 60 (Wikipedia:Morse_code)
#define DITS_PER_WORD   50

MorseCodeSequencer::MorseCodeSequencer()
{
   state = MCS_STATE_IDLE;
   setWPM(WPM_DEFAULT);
}

bool MorseCodeSequencer::send(char c)
{
   this->state = MCS_STATE_IDLE;

   morseBitmaskToSent = getMorseBitmask(c);
   if (morseBitmaskToSent == 0)
   {
      return false;
   }

   this->bitIndex = 7;
   this->state = MCS_STATE_TRY_TO_SEND;

   // look for sentinel
   for (int q = 7; q >= 1; q--)
   {
      if (morseBitmaskToSent & _BV(q))
      {
         bitIndex = q - 1;
         break;
      }
   }

   return true;
}

bool MorseCodeSequencer::isBusy()
{
   if (state == MCS_STATE_IDLE)
   {
      return false;
   }

   return true;
}

void MorseCodeSequencer::setWPM(uint8_t wpm)
{
   dotDuration = (1000.0 * 60.0 / (max(1.0f, (float)wpm) * DITS_PER_WORD));
   dashDuration = 3 * dotDuration;
}

MorseBitmask MorseCodeSequencer::getMorseBitmask(char c)
{
   if (c >= 'a' && c <= 'z')
   {
      return MORSE_LETTERS[c - 'a'];
   }

   return 0;
}

void MorseCodeSequencer::loop()
{
   switch (state)
   {
      case MCS_STATE_IDLE:
      {
         return;
      }
         ;
         break;
      case MCS_STATE_TRY_TO_SEND:
      {
         lastSendTime = millis();
         if (morseBitmaskToSent & _BV(bitIndex))
         {
            // send '-'
            onDashStart();
         }
         else
         {
            // send '.'
            onDotStart();
         }
         state = MCS_STATE_WAITING_FOR_END;
         break;
      }
      case MCS_STATE_WAITING_FOR_END:
      {
         if (morseBitmaskToSent & _BV(bitIndex))
         {
            // currently sending '-'
            if (millis() <= lastSendTime + dashDuration)
            {
               return;
            }
            onDashStop();
         }
         else
         {
            // currently sending '.'
            if (millis() <= lastSendTime + dotDuration)
            {
               return;
            }
            onDotStop();
         }

         lastSendTime = millis();

         if (bitIndex == 0)
         {
            state = MCS_STATE_IDLE;
         }
         else
         {
            // now it's time to pause
            state = MCS_STATE_WAITING_FOR_PAUSE_END;
         }
         break;
      }
      case MCS_STATE_WAITING_FOR_PAUSE_END:
      {
         if (millis() <= lastSendTime + dotDuration)
         {
            return;
         }

         bitIndex--;
         state = MCS_STATE_TRY_TO_SEND;
         break;
      }
   }
}
