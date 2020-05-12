/*
 * StepperGauge.cpp
 *
 *  Created on: 3 mar 2020
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "StepperGauge.h"

#define STEPS_PIN 13
#define DIR_PIN A0
#define STEPPER_DELAY_IN_MICROS 100
// defines how many full steps required per full possible rotation
#define STEPS_PER_MAX_ANGLE 185

StepperGauge::StepperGauge() :
      AbstractGauge()
{
   setAngleRange(0, STEPS_PER_MAX_ANGLE);
}

void StepperGauge::init()
{
   pinMode(STEPS_PIN, OUTPUT);
   pinMode(DIR_PIN, OUTPUT);
}

/***
 * We do not use angles here. In stepper motor we use direct the steps.
 * Calling this method will have no effect.
 *
 * @param min minimal value, internally set to 0
 * @param max maximal value, internally set to STEPS_PER_MAX_ANGLE
 */
void StepperGauge::setAngleRange(int16_t min, int16_t max)
{
   AbstractGauge::setAngleRange(0, STEPS_PER_MAX_ANGLE);
}

/***
 * In stepper motor the deltaAngle is actually the number of steps.
 *
 * @param deltaAngle the number of steps
 */
void StepperGauge::updateDriverDelta(int16_t deltaAngle)
{
   if (deltaAngle > 0)
   {
      digitalWrite(DIR_PIN, LOW);
   }
   else
   {
      digitalWrite(DIR_PIN, HIGH);
   }

   uint16_t max = abs(deltaAngle);

   for (uint16_t q = 0; q < max; q++)
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
