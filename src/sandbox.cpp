#include <Arduino.h>
#include "TSMP58000.h"

#define RECEIVER_PIN 2

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
}

TSMP58000 tsmp;

void loop()
{
   Serial.print(F("Waiting 3 sec for user click..."));
   if (tsmp.read())
   {
      Serial.println(F(""));
      tsmp.dump();
   }
   else
   {
      Serial.println(F(" nothing received"));
      tsmp.dump();
   }
}

#define BUFFER_SIZE 512
#define FRAME_TIMEOUT 7000
uint16_t table[BUFFER_SIZE];
volatile uint8_t currentState;
uint16_t index = 0;

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
   return 1000000.0 / (((double) toggleFreqDur) / ((double) toggleCount)) / 2.0;
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

