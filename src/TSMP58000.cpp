/*
 * TSMP58000.cpp
 *
 *  Created on: 25.04.2018
 *      Author: wmarkowski
 */
#include <Arduino.h>
#include "TSMP58000.h"

#define RECEIVER_PIN D2

#define STATE_IDLE 0
#define STATE_TOGGLE 1
#define STATE_SPACE_LOW 2
#define STATE_SPACE_HIGH 3
#define STATE_END 4

bool TSMP58000::read(Array<IRData>* receivedData)
{
   uint8_t oldPinState = HIGH;
   uint8_t newPinState;
   uint8_t state = STATE_IDLE;
   receivedData->clear();
   //
   toggleDurationInMicros = 0;
   toggleCount = 0;

   uint32_t readStartMicros = micros();
   uint32_t currentMicros = readStartMicros;
   uint32_t toggleStartMicros = readStartMicros;
   uint32_t lastToggleMicros = readStartMicros;

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
               if (currentMicros - readStartMicros > 1000000)
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
                  IRData irData;
                  irData.type = IR_TYPE_TOGGLE;
                  irData.duration = lastToggleMicros - toggleStartMicros;
                  receivedData->add(irData);
                  if (newPinState == LOW)
                  {
                     state = STATE_SPACE_LOW;
                  }
                  else
                  {
                     state = STATE_SPACE_HIGH;
                  }

                  // for signal frequency calculation
                  if (toggleDurationInMicros == 0)
                  {
                     toggleDurationInMicros = lastToggleMicros
                           - toggleStartMicros;
                  }

                  break;
               }
            }
            // pin has changed
            oldPinState = newPinState;
            lastToggleMicros = currentMicros;

            // for signal frequency calculation
            if (toggleDurationInMicros == 0)
            {
               toggleCount++;
            }

            break;
         }
         case STATE_SPACE_LOW:
         {
            while (oldPinState == (newPinState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               if (currentMicros - lastToggleMicros > 30000)
               {
                  IRData irData;
                  irData.type = IR_TYPE_SPACE_LOW;
                  irData.duration = currentMicros - lastToggleMicros;
                  receivedData->add(irData);

                  state = STATE_END;

                  return true;
               }
            }

            oldPinState = newPinState;
            IRData irData;
            irData.type = IR_TYPE_SPACE_LOW;
            irData.duration = currentMicros - lastToggleMicros;
            receivedData->add(irData);

            toggleStartMicros = currentMicros;
            lastToggleMicros = currentMicros;
            state = STATE_TOGGLE;

            break;
         }
         case STATE_SPACE_HIGH:
         {
            while (oldPinState == (newPinState = digitalRead(RECEIVER_PIN)))
            {
               currentMicros = micros();
               if (currentMicros - lastToggleMicros > 30000)
               {
                  IRData irData;
                  irData.type = IR_TYPE_SPACE_HIGH;
                  irData.duration = currentMicros - lastToggleMicros;
                  receivedData->add(irData);

                  state = STATE_END;

                  return true;
               }
            }

            oldPinState = newPinState;
            IRData irData;
            irData.type = IR_TYPE_SPACE_HIGH;
            irData.duration = currentMicros - lastToggleMicros;
            receivedData->add(irData);

            toggleStartMicros = currentMicros;
            lastToggleMicros = currentMicros;
            state = STATE_TOGGLE;

            break;
         }
      }
   }
   return false;
}

void TSMP58000::dump(Array<IRData>* array)
{
   Serial.print(F("Odebralem "));
   Serial.print(array->getSize());
   Serial.println(F(" danych:"));

   for (uint8_t q = 0; q < array->getSize(); q++)
   {
      IRData* ptr = array->peek(q);
      switch (ptr->type)
      {
         case IR_TYPE_TOGGLE:
            Serial.print(F("T"));
            break;
         case IR_TYPE_SPACE_LOW:
            Serial.print(F("L"));
            break;
         case IR_TYPE_SPACE_HIGH:
            Serial.print(F("H"));
            break;
         default:
            Serial.print(ptr->type);
      }
      Serial.print(F("  "));
      Serial.println(ptr->duration);
   }
   Serial.print(F("Toggle duration [us]: "));
   Serial.println(toggleDurationInMicros);
   Serial.print(F("Toggle count: "));
   Serial.println(toggleCount);
   double freq = 500.0 * ((double) toggleCount)
         / ((double) toggleDurationInMicros);
   Serial.print(F("Signal frequency [kHz]: "));
   Serial.println(freq);
}
