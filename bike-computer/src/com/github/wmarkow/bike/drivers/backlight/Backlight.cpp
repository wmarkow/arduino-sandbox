/*
 * Backlight.cpp
 *
 *  Created on: 3 lis 2019
 *      Author: Witold Markowski
 */

#include <Arduino.h>

#include "Backlight.h"

#define BACKLIGHT_PWM_PIN 9

void Backlight::init()
{
    pinMode(BACKLIGHT_PWM_PIN, OUTPUT);
    setValuePercent(0);
}

void Backlight::setValuePercent(uint8_t value)
{
    if (value > 100)
    {
        value = 100;
    }

    value = map(value, 0, 100, 0, 255);
    value = 255 - value;

    analogWrite(BACKLIGHT_PWM_PIN, value);
}
