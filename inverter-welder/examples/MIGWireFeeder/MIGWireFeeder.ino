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

BasicStepperDriver stepper(MOTOR_STEPS, PIN_DIR, PIN_STEP, PIN_ENABLE);

void setup()
{
   Serial.begin(57600);

   stepper.setEnableActiveState(LOW);
   stepper.begin(RPM, MICROSTEPS);
}

void loop()
{
   /*
    * Moving motor one full revolution using the degree notation
    */
   Serial.println("Rotate 360 ...");
   stepper.rotate(360);

   Serial.println("Wait 1 second ...");
   delay(1000);
}
