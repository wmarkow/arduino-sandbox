/* dumpFreq.ino Example sketch for IRLib2
 * Illustrates how to simultaneously decode an IR stream and
 * measure modulation frequency using the IRfrequency class in
 * the IRLibFreq library. You must connect an IR learner such
 * as TSMP58000 to a hardware interrupt pin. Rather than use the
 * IRrecv receiver we recommend using the IRrecvPCI or IRrecvLoop
 * receiver because the 50 microsecond interrupts from IRrecv
 * can cause inaccurate results.
 */
#include <IRLibAll.h>//Note this also includes "IRLibFreq.h"
//#include <IRLibRecvPCI.h>
//#include <IRLibFreq.h>
//#include <IRLibDecodeBase.h>
//#include <IRLibCombo.h>

//NOTE: Previous versions of IRLib required you to pass the
// interrupt number to be passed to the built-in "attachInterrupt()"
// function however starting with IRLib 2.x you now pass the pin number.
#define RECEIVER_PIN 2
#define FREQUENCY_PIN 3

//IRrecvPCI myReceiver(RECEIVER_PIN);
//IRrecvLoop myReceiver(RECEIVER_PIN); //comment out previous line and un-comment this for loop version
//IRfrequency myFreq(FREQUENCY_PIN);
//IRdecode myDecoder;

bool getResults(void);
bool getResultsAsBits(void);
void dump();

uint32_t toggleFreqDur = 0;
uint16_t toggleCount = 0;

void setup()
{
   Serial.begin(9600);
   delay(2000);
   while (!Serial)
      ; //delay for Leonardo
   if (F_CPU < 16000000)
   {
      Serial.println(
            F("WARNING: CPU speed less than 16 MHz will be inaccurate"));
      Serial.print(F("for frequencies over 45 kHz. Your CPU is:"));
      Serial.print(F_CPU / 1000000, DEC);
      Serial.println(F(" Mhz"));
   }
   int8_t intrNum = digitalPinToInterrupt(FREQUENCY_PIN);
   if (intrNum == NOT_AN_INTERRUPT)
   {
      Serial.println(F("Invalid frequency pin number."));
      while (1)
      {
      }; //infinite loop because of fatal error
   }
   Serial.print(F("Frequency interrupt="));
   Serial.print(intrNum, DEC);
   Serial.print(F(" Pin="));
   Serial.println(FREQUENCY_PIN, DEC);
   intrNum = digitalPinToInterrupt(RECEIVER_PIN);
   if (intrNum == NOT_AN_INTERRUPT)
   {
      Serial.println(F("Invalid receiver pin number."));
      while (1)
      {
      }; //infinite loop because of fatal error
   }
   Serial.print(F("Receiver interrupt="));
   Serial.print(intrNum, DEC);
   Serial.print(F(" Pin="));
   Serial.println(RECEIVER_PIN, DEC);

//   myReceiver.enableIRIn(); // Start the receiver
//   myFreq.enableFreqDetect(); //starts interrupt routine to compute frequency
}

void loop()
{
   // decode protocol
//  if (myReceiver.getResults()) {
//     myReceiver.dump();
//
////    myDecoder.decode();
//
////    myDecoder.dumpResults();
//    myReceiver.enableIRIn();
//  }

   // detect frequency
//  if (myFreq.haveData()) {
//      delay(500);  //it couldn't hurt to collect a little more just in case
//      myFreq.disableFreqDetect();
//      myFreq.dumpResults(true);//Change to "true" for more detail
//      myFreq.enableFreqDetect();//Zero out previous results and restart ISR
//    }

   // moj kawalek kodu
   if (getResultsAsBits())
   {
      dump();
   }
}

#define BUFFER_SIZE 512
#define FRAME_TIMEOUT 7000
uint16_t table[BUFFER_SIZE];
volatile currentState_t currentState;
uint16_t index = 0;

#define MY_STATE_IDLE 0
#define MY_STATE_WAITING_FOR_USER_CLICK 1
#define MY_STATE_CHECKING_STARTUP 2
#define MY_STATE_COLLECT_DATA 3
#define MY_STATE_JUST_COUNT 4
#define MY_STATE_FINISHED 10

bool getResults(void)
{
   uint8_t oldState = HIGH;
   uint8_t newState;
   uint32_t startTime;
   uint32_t veryStartTime;
   uint32_t endTime;
   volatile uint32_t currentMicros;
   uint32_t firstChangeTimeStamp;

   startTime = micros();
   veryStartTime = startTime;
   currentState = MY_STATE_IDLE;
   index = 0;

   while (currentState != MY_STATE_FINISHED)
   {
      currentMicros = micros();
      switch (currentState)
      {
         case MY_STATE_IDLE:
         {
            Serial.println(F("Waiting 3 sec for user click"));
            currentState = MY_STATE_WAITING_FOR_USER_CLICK;
            break;
         }
         case MY_STATE_WAITING_FOR_USER_CLICK:
         {
            while (oldState == (newState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               uint32_t diff = currentMicros - veryStartTime;
               if (diff > 3000000)
               {
                  currentState = MY_STATE_FINISHED;
                  return true;
               }
            }
            currentMicros = micros();
            firstChangeTimeStamp = currentMicros;
            table[index] = currentMicros - startTime;
            startTime = firstChangeTimeStamp;
            oldState = newState;
            index++;
//            currentState = MY_STATE_CHECKING_STARTUP;
            currentState = MY_STATE_COLLECT_DATA;
            break;
         }
         case MY_STATE_CHECKING_STARTUP:
         {
            while (oldState == (newState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               if (oldState == HIGH)
               {
                  if ((currentMicros - startTime) > 3000000)
                  {
                     currentState = MY_STATE_FINISHED;
                     break;
                  }
               }
            }
            // the pin has changed
            uint32_t duration = micros() - startTime;
            if (duration < 100)
            {
               // do not set this in the table
               oldState = newState;
               startTime = micros();
               continue;
            }
            else
            {
               table[index] = duration;
               index++;
               oldState = newState;
               startTime = micros();

//               Serial.println(F("Mam cos"));
//               Serial.println(duration);
//               Serial.println(currentMicros - firstChangeTimeStamp);
//
//               return true;
            }

            currentState = MY_STATE_COLLECT_DATA;
            break;
         }
         case MY_STATE_COLLECT_DATA:
         {
            while (oldState == (newState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               if (oldState == HIGH)
               {
                  if ((currentMicros - startTime) > 3000000)
                  {
                     currentState = MY_STATE_FINISHED;
                     break;
                  }
               }
            }

            currentMicros = micros();
            table[index] = currentMicros - startTime;
            oldState = newState;
            startTime = currentMicros;
            if (++index >= BUFFER_SIZE)
            {
               currentState = MY_STATE_JUST_COUNT;
            }
            break;
         }
         case MY_STATE_JUST_COUNT:
         {
            while (oldState == (newState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               if (oldState == HIGH)
               {
                  if ((currentMicros - startTime) > 3000000)
                  {
                     currentState = MY_STATE_FINISHED;
                     break;
                  }
               }
            }

            currentMicros = micros();
            oldState = newState;
            index++;
            startTime = currentMicros;
            break;
         }
      }
   }

   return true;
}

#define MY_STATE2_IDLE 0
#define MY_STATE2_WAITING_FOR_USER_CLICK 1
#define MY_STATE2_TOGGLING 2
#define MY_STATE2_SILENCE 3
#define MY_STATE2_FINISHED 10

bool getResultsAsBits(void)
{
   uint8_t oldState = HIGH;
   uint32_t lastToggleTime;
   uint32_t firstToggleTime;
   uint8_t newState;
   uint32_t startTime;
   volatile uint32_t currentMicros;

   currentState = MY_STATE2_IDLE;
   index = 0;
   toggleFreqDur = 0;
   uint16_t toggleCount = 0;
   startTime = micros();

   while (currentState != MY_STATE2_FINISHED)
   {
      currentMicros = micros();
      switch (currentState)
      {
         case MY_STATE2_IDLE:
         {
            Serial.println(F("Waiting 3 sec for user click"));
            currentState = MY_STATE2_WAITING_FOR_USER_CLICK;
            break;
         }
         case MY_STATE2_WAITING_FOR_USER_CLICK:
         {
            while (oldState == (newState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               uint32_t diff = currentMicros - startTime;
               if (diff > 3000000)
               {
                  return false;
               }
            }
            firstToggleTime = currentMicros;
            lastToggleTime = currentMicros;
            oldState = newState;
            currentState = MY_STATE2_TOGGLING;

            break;
         }
         case MY_STATE2_TOGGLING:
         {
            while (oldState == (newState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();

               if ((currentMicros - lastToggleTime) > 100)
               {
                  // can calculate frequency now
                  if (toggleFreqDur == 0)
                  {
                     toggleFreqDur = lastToggleTime - firstToggleTime;
                  }
                  currentState = MY_STATE2_SILENCE;
                  break;
               }
            }
            // the pin has changed
            lastToggleTime = currentMicros;
            oldState = newState;
            if (toggleFreqDur == 0)
            {
               toggleCount++;
            }

            break;
         }
         case MY_STATE2_SILENCE:
         {
            while (oldState == (newState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               if ((currentMicros - lastToggleTime) > 30000)
               {
                  currentState = MY_STATE2_FINISHED;
                  // but what did we received as the last bit? 0 or 1?
                  uint16_t lastToggleDuration = lastToggleTime
                        - firstToggleTime;
                  Serial.println(lastToggleDuration);
                  if (lastToggleDuration > 400 && lastToggleDuration < 700)
                  {
                     // logic ZERO detected (or ONE, we do not know yet)
                     table[index] = 0;
                     index++;
                     return true;
                  }
                  if (lastToggleDuration > 1400 && lastToggleDuration < 1700)
                  {
                     // logic ONE detected (or ZERO, we do not know yet)
                     table[index] = 1;
                     index++;
                     return true;
                  }

                  // protocol error
                  // something wrong with the timing
                  Serial.print(F("Protocol error. Duration is"));
                  Serial.println(lastToggleDuration);
                  return false;
               }
            }

            // toggling detected
            uint16_t duration = currentMicros - lastToggleTime;
            oldState = newState;
            lastToggleTime = currentMicros;

            if (duration > 400 && duration < 700)
            {
               // logic ZERO detected (or ONE, we do not know yet)
               table[index] = 0;
               index++;
               firstToggleTime = currentMicros;

               currentState = MY_STATE2_TOGGLING;
               break;
            }
            if (duration > 1400 && duration < 1700)
            {
               // logic ONE detected (or ZERO, we do not know yet)
               table[index] = 1;
               index++;
               firstToggleTime = currentMicros;

               currentState = MY_STATE2_TOGGLING;
               break;
            }

            // something wrong with the timing
            Serial.print(F("Protocol error. Duration is"));
            Serial.println(duration);

            return false;
         }
      }
   }

   return true;
}

double calcFreq()
{
   return 1000000.0 / (((double)toggleFreqDur) / ((double)toggleCount)) / 2.0;
//   return 1000000L / (toggleFreqDur / toggleCount) / 2;
}

void dump()
{
   uint16_t i;
   Serial.print(F("Odebralem: "));
   Serial.println(index);
   Serial.print(F("Freq: "));
   Serial.println(calcFreq());
   Serial.println(toggleFreqDur);
   Serial.println(toggleCount);

   uint16_t forLoop = min(index, BUFFER_SIZE);

   for (i = 0; i < forLoop; i++)
   {
      uint16_t interval = table[i];
      Serial.print(interval, DEC);
      Serial.print("\t");
      if ((i % 4) == 0)
         Serial.print(F("\t "));
      if ((i % 8) == 0)
         Serial.println();
      if ((i % 32) == 0)
         Serial.println();
   }
   Serial.println();
}

