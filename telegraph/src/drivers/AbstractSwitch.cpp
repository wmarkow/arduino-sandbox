#include <Arduino.h>
#include "AbstractSwitch.h"

#define DEBOUNCE_TIME_IN_MILLIS 10

AbstractSwitch::AbstractSwitch(uint8_t pin)
{
   this->pin = pin;
   this->state = STATE_OFF;
   this->firstTimestamp = 0;
}

void AbstractSwitch::init()
{
   pinMode(pin, INPUT_PULLUP);
   digitalWrite(pin, HIGH);
}

void AbstractSwitch::loop()
{
   int readPin = digitalRead(pin);

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
         if (millis() - firstTimestamp < DEBOUNCE_TIME_IN_MILLIS)
         {
            break;
         }
         if (readPin == LOW)
         {
            // STATE_ON detected
            state = STATE_ON;
            onSwitchOnInternal();
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
         if (millis() - firstTimestamp < DEBOUNCE_TIME_IN_MILLIS)
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
            onSwitchOffInternal();
         }
         break;
   }
}

bool AbstractSwitch::isPressed()
{
   if(state == STATE_ON)
   {
      return true;
   }

   return false;
}
