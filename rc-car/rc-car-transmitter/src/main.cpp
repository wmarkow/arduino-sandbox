#include <Arduino.h>
#include "Joystick.h"

#define JOYSTICK_X_INPUT A0
#define JOYSTICK_Y_INPUT A1
#define TURBO_BUTTON_INPUT 2

unsigned long lastDisplayTime;
Joystick joystick(JOYSTICK_X_INPUT, JOYSTICK_Y_INPUT);

void setup()
{
    pinMode(TURBO_BUTTON_INPUT, INPUT);

    Serial.begin(9600);

    lastDisplayTime = 0;
    joystick.setReverseY(true);
}

void loop(void)
{
    int16_t joystickX = joystick.readX();
    int16_t joystickY = joystick.readY();
    uint8_t turboButton = digitalRead(TURBO_BUTTON_INPUT);

    if (millis() - lastDisplayTime > 100)
    {
        char tbs[50];
        sprintf(tbs, "X=%04d Y=%04d T=%1d", joystickX, joystickY, turboButton);

        Serial.println(tbs);

        lastDisplayTime = millis();
    }
}
