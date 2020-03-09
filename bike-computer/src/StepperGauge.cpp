/*
 * StepperGauge.cpp
 *
 *  Created on: 3 mar 2020
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "StepperGauge.h"

#define STEPS_PIN 2
#define DIR_PIN 3
#define STEPPER_DELAY_IN_MICROS 100

StepperGauge::StepperGauge() : AbstractGauge()
{
}

void StepperGauge::init()
{
	pinMode(STEPS_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);
}

void StepperGauge::updateDriverDelta(int16_t deltaAngle)
{
	if(deltaAngle > 0)
	{
        digitalWrite(DIR_PIN, LOW);
	}
	else
	{
		digitalWrite(DIR_PIN, HIGH);
	}

	uint16_t max = abs(deltaAngle);

	for(uint16_t q = 0 ; q < max ; q++)
	{
	    digitalWrite(STEPS_PIN, HIGH);
	    delayMicroseconds(STEPPER_DELAY_IN_MICROS);
	    digitalWrite(STEPS_PIN, LOW);
	    delayMicroseconds(STEPPER_DELAY_IN_MICROS);
	}
}

void StepperGauge::updateDriverAbsolute(int16_t currentAngle)
{
	// nothing to do here; do not support absolute update
}
