/*
 * TSMP58000.cpp
 *
 *  Created on: 25.04.2018
 *      Author: wmarkowski
 */
#include <Arduino.h>
#include "TSMP58000.h"

#define RECEIVER_PIN 2

#define STATE_IDLE 0
#define STATE_TOGGLE 1
#define STATE_SILENCE 2
#define STATE_PRE_END 3
#define STATE_END 4

bool TSMP58000::read()
{
   uint8_t oldPinState = HIGH;
   uint8_t newPinState;
   uint8_t state = STATE_IDLE;
   currentIndex = -1;

   uint32_t readStartMicros = micros();
   uint32_t currentMicros;
   uint32_t toggleStartMicros;
   uint32_t lastToggleMicros;

   while (state != STATE_END)
   {
      currentMicros = micros();
      switch (state)
      {
         case STATE_IDLE:
         {
            while (oldPinState == (newPinState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               if (currentMicros - readStartMicros > 3000000)
               {
                  return false;
               }
            }
            // pin has changed while in IDLE state
            oldPinState = newPinState;
            toggleStartMicros = currentMicros;
            lastToggleMicros = currentMicros;
            state = STATE_TOGGLE;

            break;
         }
         case STATE_TOGGLE:
         {
            while (oldPinState == (newPinState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               if (currentMicros - lastToggleMicros > 100)
               {
                  // pin has not changed for longer time
                  currentIndex++;
                  receivedData[currentIndex].type = IR_TYPE_TOGGLE;
                  receivedData[currentIndex].duration = lastToggleMicros
                        - toggleStartMicros;
                  state = STATE_SILENCE;

                  break;
               }
            }
            // pin has changed
            oldPinState = newPinState;
            lastToggleMicros = currentMicros;

            break;
         }
         case STATE_SILENCE:
         {
            while (oldPinState == (newPinState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               if (currentMicros - lastToggleMicros > 30000)
               {
                  currentIndex++;
                  receivedData[currentIndex].type = IR_TYPE_SILENCE;
                  receivedData[currentIndex].duration = currentMicros
                        - lastToggleMicros;
                  state = STATE_END;

                  return true;
               }
            }

            oldPinState = newPinState;
            toggleStartMicros = currentMicros;
            currentIndex++;
            receivedData[currentIndex].type = IR_TYPE_SILENCE;
            receivedData[currentIndex].duration = currentMicros
                  - lastToggleMicros;
            state = STATE_TOGGLE;

            break;
         }
      }
   }
   return false;
}

uint8_t TSMP58000::getReceivedDataSize()
{
   return currentIndex + 1;
}

IRData* TSMP58000::getData(uint8_t index)
{
   if(index <= currentIndex){
      return &receivedData[index];
   }

   return NULL;
}
