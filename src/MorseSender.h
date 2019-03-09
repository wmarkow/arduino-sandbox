#ifndef MORSESENDER_H_
#define MORSESENDER_H_

#include <Arduino.h>

#define WPM_DEFAULT  12.0
// PARIS WPM measurement: 50; CODEX WPM measurement: 60 (Wikipedia:Morse_code)
#define DITS_PER_WORD   50
// Pass to SpeakerMorseSender as carrierFrequency to suppress the carrier.
#define CARRIER_FREQUENCY_NONE   0

// Bitmasks are 1 for dah and 0 for dit, in left-to-right order;
// the sequence proper begins after the first 1 (a sentinel).
// Credit for this scheme to Mark VandeWettering K6HX ( brainwagon.org ).
typedef unsigned int morseTiming_t;
typedef unsigned char morseBitmask_t; // see also MAX_TIMINGS
#define MORSE_BITMASK_HIGH_BIT   B10000000

// sentinel
#define END             0

// the most timing numbers any unit will need; ex: k = on,off,on,off,on,end = 5
#define MAX_TIMINGS     15

// Punctuation and Prosigns
#define PROSIGN_SK   'S'
#define PROSIGN_KN   'K'
#define PROSIGN_BT   'B'
typedef struct
{
   char c;
   morseBitmask_t timing;
} specialTiming;
const specialTiming MORSE_PUNCT_ETC[] =
{
{ '.', B1010101 },
{ '?', B1001100 },
{ PROSIGN_SK, B1000101 },
{ PROSIGN_KN, B110110 },
{ PROSIGN_BT, B110001 },
{ END, B1 }, };



#define              MORSE_SENDER_STATE_IDLE 0
#define MORSE_SENDER_STATE_SENDING_CHARACTER 1

class MorseSender
{
protected:
   const unsigned int pin;
   // The setOn and setOff methods would be pure virtual,
   // but that has compiler issues.
   // See: http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1167672075 .

   /**
    * Called to set put the output in 'on' state, during a dit or dah.
    */
   virtual void setOn();
   virtual void setOff();

   /**
    * Called before sending a message. Used for example to enable a
    * carrier. (Noop in the base class.)
    */
   virtual void setReady();
   virtual void setComplete();

private:
   char charsToSent[8];
   uint8_t charsToSentCount;
   uint8_t charIndex;
   uint8_t charBitIndex;
   uint8_t state;

   morseTiming_t DIT, DAH;
   String message;

   // on,off,...,wait,0 list, millis
   morseTiming_t timingBuffer[MAX_TIMINGS + 1];

   // index of the character currently being sent
   unsigned int messageIndex;
   // timing unit currently being sent
   unsigned int timingIndex;

   // when this timing unit was started
   unsigned long lastChangedMillis;

   /**
    * Copy definition timings (on only) to raw timings (on/off).
    * @return the number of 'on' timings copied
    */
   int copyTimings(morseTiming_t *rawOut, morseBitmask_t definition);

   /**
    * Fill a buffer with on,off,..,END timings (millis)
    * @return the index at which to start within the new timing sequence
    */
   unsigned int fillTimings(char c);

public:
   /**
    * Create a sender which will output to the given pin.
    */
   MorseSender(unsigned int outputPin, float wpm = WPM_DEFAULT);

   void send(char c);

   void loop();

   /**
    * To be called during the Arduino setup(); set the pin as OUTPUT.
    */
   void setup();

   /**
    * Set the words per minute (based on PARIS timing).
    */
   void setWPM(float wpm);

   /**
    * Set the duration, in milliseconds, of a DIT.
    */
   void setSpeed(morseTiming_t duration);

   /**
    * Set the message to be sent.
    * This halts any sending in progress.
    */
   void setMessage(const String newMessage);

   /**
    * Send the entirety of the current message before returning. See the "simple"
    * example, which uses sendBlocking to send one message.
    */
   void sendBlocking();

   /**
    * Prepare to send and begin sending the current message. After calling this,
    * call continueSending repeatedly until it returns false to finish sending
    * the message. See the "speeds" example, which calls startSending and
    * continueSending on two different senders.
    */
   void startSending();

   /**
    * Switch outputs on and off (and refill the internal timing buffer)
    * as necessary to continue with the sending of the current message.
    * This should be called every few milliseconds (at a significantly
    * smaller interval than a DIT) to produce a legible fist.
    *
    * @see startSending, which must be called first
    * @return false if sending is complete, otherwise true (keep sending)
    */
   boolean continueSending();

   void *operator new(size_t size);
   void operator delete(void* ptr);
};

#endif /* MORSESENDER_H_ */