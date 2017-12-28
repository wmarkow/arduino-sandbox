/*
 * MonostableSwitch.cpp
 *
 *  Created on: 03.11.2017
 *      Author: wmarkowski
 */

#include "MonostableSwitch.h"
#include <Arduino.h>

MonostableSwitch::MonostableSwitch(uint8_t pin)
{
   this->pin = pin;
   this->state = STATE_OFF;
   this->firstTimestamp = 0;
   this->onSwitchOnPtr = NULL;
   this->onSwitchOffPtr = NULL;
}

void MonostableSwitch::init()
{
   pinMode(pin, INPUT);
   digitalWrite(pin, HIGH);
}

void MonostableSwitch::loop()
{
   int readPin = readButtonState();

   switch (state)
   {
      case STATE_OFF:
         if (readPin == LOW)
         {
            state = STATE_FIRST_ON;
            firstTimestamp = millis();
         }
         break;
      case STATE_FIRST_ON:
         if (millis() - firstTimestamp < 100)
         {
            break;
         }
         if (readPin == LOW)
         {
            // STATE_ON detected
            state = STATE_ON;
            if (this->onSwitchOnPtr != NULL)
            {
               this->onSwitchOnPtr();
            }
         }
         else
         {
            state = STATE_OFF;
         }
         break;
      case STATE_ON:
         if (readPin == HIGH)
         {
            state = STATE_FIRST_OFF;
            firstTimestamp = millis();
         }
         break;
      case STATE_FIRST_OFF:
         if (millis() - firstTimestamp < 100)
         {
            break;
         }
         if (readPin == LOW)
         {
            state = STATE_ON;
         }
         else
         {
            // STATE_OFF detected
            state = STATE_OFF;
            if (this->onSwitchOffPtr != NULL)
            {
               this->onSwitchOffPtr();
            }
         }
         break;
   }
}

void MonostableSwitch::setOnSwitchOnPtr(void (*onSwitchOnPtr)())
{
   this->onSwitchOnPtr = onSwitchOnPtr;
}

void MonostableSwitch::setOnSwitchOffPtr(void (*onSwitchOffPtr)())
{
   this->onSwitchOffPtr = onSwitchOffPtr;
}

