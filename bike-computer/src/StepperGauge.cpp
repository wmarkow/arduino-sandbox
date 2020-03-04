/*
 * StepperGauge.cpp
 *
 *  Created on: 3 mar 2020
 *      Author: wmarkowski
 */

#include "StepperGauge.h"
#include <HardwareSerial.h>

#define DELTA_T_IN_MILLIS 2
#define DELTA_ANGLE 1

#define STEPS_PIN 2
#define DIR_PIN 3
#define STEP_TIME_IN_MILLIS 1


StepperGauge::StepperGauge()
{
    this->currentAngle = 0;
    this->desiredAngle = 0;
    this->lastUpdateTimeMillis = 0;
    this->minAngle = 0;
    this->maxAngle = 359;
    this->minValue = 0;
    this->maxValue = 0;
}

void StepperGauge::init()
{
	pinMode(STEPS_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);
}

/***
 * Must be constantly called to make a proper movement of the needle.
 *
 * The purpose of this method is to provide a consistent way of the needle's movement. If the gauge's default
 * movement from 0 degree to 90 degree is clockwise,
 * then this method will assure that the move from 0 to 359 will be also clockwise, and the move from the 359
 * to 0 will be counterclockwise.
 *
 */
void StepperGauge::loop()
{
    if (currentAngle == desiredAngle)
    {
        return;
    }

    if (millis() - lastUpdateTimeMillis <= DELTA_T_IN_MILLIS)
    {
        return;
    }

    if (currentAngle < desiredAngle)
    {
        currentAngle += DELTA_ANGLE;
        if (currentAngle >= desiredAngle)
        {
            currentAngle = desiredAngle;
        }
        // plus one step (clockwise)
        digitalWrite(DIR_PIN, LOW);
        digitalWrite(STEPS_PIN, HIGH);
//        delay(STEP_TIME_IN_MILLIS);
        delayMicroseconds(100);
        digitalWrite(STEPS_PIN, LOW);
//        delay(STEP_TIME_IN_MILLIS);
        delayMicroseconds(100);
        Serial.println("step+");
    }
    else if (currentAngle > desiredAngle)
    {
        currentAngle -= DELTA_ANGLE;
        if (currentAngle <= desiredAngle)
        {
            currentAngle = desiredAngle;
        }
        // minus one step
        digitalWrite(DIR_PIN, HIGH);
        digitalWrite(STEPS_PIN, HIGH);
//        delay(STEP_TIME_IN_MILLIS);
        delayMicroseconds(100);
        digitalWrite(STEPS_PIN, LOW);
//        delay(STEP_TIME_IN_MILLIS);
        delayMicroseconds(100);
        Serial.println("step-");
    }

    //     TODO: step the needle to currentAngle
    //    driver->writeLogo(logoNumber, currentAngle);

    lastUpdateTimeMillis = millis();


//    int steps = 10;
//    int dir = 11;
//    int stepTime=100;
//
//
//
//    void setup() {
//
//      pinMode(steps, OUTPUT);
//      pinMode(dir, OUTPUT);
//    }
//
//
//    void loop() {
//      digitalWrite(dir, HIGH);
//      digitalWrite(steps, HIGH);
//      delay(stepTime);
//      digitalWrite(steps, LOW);
//      delay(stepTime);

}

/***
 * Sets the minimal and maximal possible angle that the needle can be set.
 *
 * @param min minimal value of angle from -359 to 359
 * @param max maximal value of angle from -359 to 359
 */
void StepperGauge::setAngleRange(int16_t min, int16_t max)
{
    this->minAngle = min;
    this->maxAngle = max;
}

/***
 * Sets the needle to the specific angle.
 * A {@link setAngleRange} must be called before to make this method work correctly.
 *
 * @param angle from 0 to 359
 */
void StepperGauge::setAngle(int16_t angle)
{
    if (angle > 359)
    {
        this->desiredAngle = 359;

        return;
    }

    this->desiredAngle = angle;
}

/***
 * Convenient method to set the needle in percents between minimal and maximal possible angle values.
 * A {@link setAngleRange} must be called before to make this method work correctly.
 *
 * @param percents
 */
void StepperGauge::setAnglePercents(uint8_t percents)
{
    uint16_t angle = map(percents, 0, 100, minAngle, maxAngle);
    setAngle(angle);
}

/***
 * A usufel method to bind the angles with a real values displayed by the gauge.
 * A {@link setAngleRange} must be called to make this method work correctly.
 *
 * @param min minimal value displayed by the gauge. It corresponds to the minimal angle of gauge.
 * @param max maximal value displayed by the gauge. It corresponds to the maximal angle of gauge.
 */
void StepperGauge::setValueRange(int16_t min, int16_t max)
{
    this->minValue = min;
    this->maxValue = max;
}

/***
 * Makes the gauge to set its needle to a specific value.
 * A {@link setValueRange} must be called to make this method work correctly.
 *
 * @param value
 */
void StepperGauge::setValue(int16_t value)
{
    uint16_t angle = map(value, minValue, maxValue, minAngle, maxAngle);
    setAngle(angle);
}

/***
 * Checks if the needle is on the way to its destination point.
 *
 * @return true if the needle is moving to the destination point
 *         false if the needle is in its destination point and not moving
 */
bool StepperGauge::isAdjusting()
{
    if (currentAngle != desiredAngle)
    {
        return true;
    }

    return false;
}


