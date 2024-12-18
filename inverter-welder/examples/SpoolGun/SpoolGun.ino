#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 60

// Define min and max possible wire speeds in [m/min]
#define MIN_WIRE_SPEED 0.5
#define MAX_WIRE_SPEED 5.0
// Define wire feeder gear diameter in m
#define WIRE_FEEDER_GEAR_DIAMETER 0.011

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
// Wire speed potentiometer pin
#define PIN_WIRE_SPEED A0 // from Abort pin of CNC shield

BasicStepperDriver stepper(MOTOR_STEPS, PIN_DIR, PIN_STEP, PIN_ENABLE);

int lastButtonState = HIGH;
int loopGetButtonState();
void loopForContinuousWelding();
void loopForSpotWelding(int lastButtonState, int currentButtonState);

void setup()
{
   Serial.begin(115200);

   pinMode(PIN_BUTTON, INPUT);
   digitalWrite(PIN_BUTTON, HIGH);

   pinMode(PIN_WIRE_SPEED, INPUT);

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

      // uncomment for spot welding
      //loopForSpotWelding(HIGH, LOW);
   }

   if (lastButtonState == LOW && buttonState == HIGH)
   {
      Serial.println("Button released...");

      lastButtonState = buttonState;

      // comment out for spot welding
      stepper.stop();
   }

   // comment out for spot welding
   loopForContinuousWelding();

   // uncomment for spot welding
   //loopForSpotWelding(lastButtonState, buttonState);
}

void loopForContinuousWelding()
{
   if (lastButtonState == LOW)
   {
      // check wire speed potentiometer
      float analogVal = analogRead(PIN_WIRE_SPEED);
      float wireSpeed = (analogVal / 1024.0) * (MAX_WIRE_SPEED - MIN_WIRE_SPEED) + MIN_WIRE_SPEED;
      float rpm = wireSpeed / (PI * WIRE_FEEDER_GEAR_DIAMETER);

      Serial.print(wireSpeed);
      Serial.print(" ");
      Serial.println(rpm);
      // Switch motor on. Calculate move to fill one second.
      int stepsPerSecond = rpm / 60 * MOTOR_STEPS;
      stepper.setRPM(rpm);
      stepper.enable();
      stepper.startMove(stepsPerSecond);

      // when button is pressed execute stepper action
      stepper.nextAction();
   }
   else
   {
      stepper.stop();
      stepper.disable();
   }
}

void loopForSpotWelding(int lastButtonState, int currentButtonState)
{
   if (lastButtonState == HIGH && currentButtonState == LOW)
   {
      // switch motor on for specific amount of time
      // make one rotation in one second
      int stepsPerSecond = RPM / 60 * MOTOR_STEPS;
      double shotDurationSecond = 0.25;
      int steps = stepsPerSecond * shotDurationSecond;
      stepper.enable();
      stepper.startMove(steps);
   }

   stepper.nextAction();

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
