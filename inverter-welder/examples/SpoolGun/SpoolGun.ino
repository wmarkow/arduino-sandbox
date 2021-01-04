#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 60

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define PIN_DIR 5    // from X driver direction of CNC shield
#define PIN_STEP 2   // from X driver step of CNC shield
#define PIN_ENABLE 8 // from EN pin of CNC shield

// Start/stop button pin
#define PIN_BUTTON 9 // from X limit switch of CNC shield

BasicStepperDriver stepper(MOTOR_STEPS, PIN_DIR, PIN_STEP, PIN_ENABLE);

int lastButtonState = HIGH;
int loopGetButtonState();

void setup()
{
   Serial.begin(57600);

   pinMode(PIN_BUTTON, INPUT);
   digitalWrite(PIN_BUTTON, HIGH);

   stepper.setEnableActiveState(LOW);
   stepper.begin(RPM, MICROSTEPS);
}

void loop()
{
   int buttonState = loopGetButtonState();

   if (lastButtonState == HIGH && buttonState == LOW)
   {
      Serial.println("Button pressed...");

      lastButtonState = buttonState;

      // switch motor on
      // make one rotation in one second
      int stepsPerSecond = RPM / 60 * MOTOR_STEPS;
      double shotDurationSecond = 1;
      int steps = stepsPerSecond * shotDurationSecond;
      stepper.enable();
      stepper.startMove(steps);
   }

   if (lastButtonState == LOW && buttonState == HIGH)
   {
      Serial.println("Button released...");

      lastButtonState = buttonState;

      stepper.stop();
   }

   if (buttonState == LOW)
   {
      // when button is pressed execute stepper action
      stepper.nextAction();
   }
   else
   {
      stepper.stop();
      stepper.disable();
   }

   if (stepper.getCurrentState() == BasicStepperDriver::STOPPED)
   {
      // when the stepper action is finished (but the button may be still pressed)
      // then disable motor
      stepper.stop();
      stepper.disable();
   }
}

long firstDebounceMillis = 0;
int buttonStateCandidate = HIGH;
int buttonState = HIGH;

int loopGetButtonState()
{
   if (firstDebounceMillis == 0)
   {
      buttonStateCandidate = digitalRead(PIN_BUTTON);
      firstDebounceMillis = millis();

      return buttonState;
   }

   if (millis() - firstDebounceMillis > 100)
   {
      if (digitalRead(PIN_BUTTON) == buttonStateCandidate)
      {
         buttonState = buttonStateCandidate;
      }
      firstDebounceMillis = 0;
   }

   return buttonState;
}
