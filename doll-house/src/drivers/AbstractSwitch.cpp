/*
 * AbstractSwitch.cpp
 *
 *  Created on: 26.07.2017
 *      Author: wmarkowski
 */
#include <Arduino.h>
#include "AbstractSwitch.h"

AbstractSwitch::AbstractSwitch()
{
    this->state = STATE_OFF;
    this->firstTimestamp = 0;
}

void AbstractSwitch::loop()
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
            onSwitchOffInternal();
        }
        break;
    }
}
