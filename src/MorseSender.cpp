#include "MorseSender.h"

// MorseSender
int MorseSender::copyTimings(morseTiming_t *rawOut, morseBitmask_t definition)
{
   int t = 0;
   boolean foundSentinel = false;
   for (morseBitmask_t mask = MORSE_BITMASK_HIGH_BIT; mask > 0;
         mask = mask >> 1)
   {
      boolean isDah = (mask & definition) > 0;
      if (!foundSentinel)
      {
         if (isDah)
         {
            foundSentinel = true;
         }
         continue;
      }
      rawOut[2 * t] = isDah ? DAH : DIT;
      rawOut[2 * t + 1] = DIT;
      t++;
   }
   return t;
}
unsigned int MorseSender::fillTimings(char c)
{
   int t = 0;
   unsigned int start = 0;
   if (c >= 'a' && c <= 'z')
   {
      //t = copyTimings(timingBuffer, MORSE_LETTERS[c - 'a']);
   }
   else if (c >= '0' && c <= '9')
   {
      int n = c - '0';
      boolean ditsFirst = (n <= 5);
      if (!ditsFirst)
      {
         n -= 5;
      }
      while (t < 5)
      {
         timingBuffer[2 * t] = ((t < n) == ditsFirst) ? DIT : DAH;
         timingBuffer[2 * t + 1] = DIT;
         t++;
      }
   }
   else
   {
      int s = 0;
      while (MORSE_PUNCT_ETC[s].c != END)
      {
         if (MORSE_PUNCT_ETC[s].c == c)
         {
            t = copyTimings(timingBuffer, MORSE_PUNCT_ETC[s].timing);
            break;
         }
         s++;
      }
      if (MORSE_PUNCT_ETC[s].c == END)
      {
         start = t = 1; // start on a space
      }
   }

   timingBuffer[2 * t - 1] = DAH;
   timingBuffer[2 * t] = END;

   /*
    Serial.print("Refilled timing buffer for '");
    Serial.print(c);
    Serial.print("': ");
    int i = start;
    while(timingBuffer[i] != END)
    {
    Serial.print((int)timingBuffer[i]);
    Serial.print(", ");
    i++;
    }
    Serial.println("END");
    */

   return start;
}

// see note in header about pure-virtual-ness
void MorseSender::setOn()
{
}
;
void MorseSender::setOff()
{
}
;

// noop defaults
void MorseSender::setReady()
{
}
;
void MorseSender::setComplete()
{
}
;

MorseSender::MorseSender(unsigned int outputPin, float wpm) :
      pin(outputPin)
{
   setWPM(wpm);
}

void MorseSender::setup()
{
   pinMode(pin, OUTPUT);
}

void MorseSender::setWPM(float wpm)
{
   setSpeed((morseTiming_t) (1000.0 * 60.0 / (max(1.0f, wpm) * DITS_PER_WORD)));
}

void MorseSender::setSpeed(morseTiming_t duration)
{
   DIT = max(duration, (morseTiming_t ) 1);
   DAH = 3 * DIT;
}

void MorseSender::setMessage(const String newMessage)
{
   message = newMessage;

   // Force startSending() before continueSending().
   messageIndex = message.length();

   // If a different message was in progress, make sure it stops cleanly.
   if (timingIndex % 2 == 0)
   {
      setOff();
   }
}

void MorseSender::sendBlocking()
{
   //Serial.println("Sending blocking: ");
   //Serial.println(message);
   startSending();
   while (continueSending())
      ;
}

void MorseSender::startSending()
{
   messageIndex = 0;
   if (message.length() == 0)
   {
      return;
   }
   timingIndex = fillTimings(message[0]);
   setReady();
   if (timingIndex % 2 == 0)
   {
      setOn();
      //Serial.print("Starting with on, duration=");
   }
   else
   {
      //Serial.print("Starting with off, duration=");
   }
   lastChangedMillis = millis();
   //Serial.println((int)timingBuffer[timingIndex]);
}

boolean MorseSender::continueSending()
{
   if (messageIndex >= message.length())
   {
      return false;
   }

   unsigned long elapsedMillis = millis() - lastChangedMillis;
   if (elapsedMillis < timingBuffer[timingIndex])
   {
      return true;
   }

   timingIndex++;
   if (timingBuffer[timingIndex] == END)
   {
      messageIndex++;
      if (messageIndex >= message.length())
      {
         setOff();
         setComplete();
         return false;
      }
      timingIndex = fillTimings(message[messageIndex]);
   }

   lastChangedMillis += elapsedMillis;
   //Serial.print("Next is       ");
   if (timingIndex % 2 == 0)
   {
      //Serial.print("(on) ");
      setOn();
   }
   else
   {
      //Serial.print("(off) ");
      setOff();
   }
   //Serial.println((int)timingBuffer[timingIndex]);

   return true;
}

void MorseSender::send(char c)
{
   charsToSent[0] = c;
   charsToSentCount = 1;
   charIndex = 0;
   charBitIndex = 7;
   state = MORSE_SENDER_STATE_IDLE;
}

void MorseSender::loop()
{
   switch (state)
   {
      case MORSE_SENDER_STATE_IDLE:
      {
         if (charsToSentCount > 0)
         {
            state = MORSE_SENDER_STATE_SENDING_CHARACTER;
            charBitIndex = 7;
         }
         break;
      }
      case MORSE_SENDER_STATE_SENDING_CHARACTER:
      {

         break;
      }
   }
}
