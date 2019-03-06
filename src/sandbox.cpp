#include "Arduino.h"

#define TELEGRAPH_KEY_PIN 8
#define BUZZER_PIN 3
#define KEY_DEBOUNCE_MILLIS 10

unsigned long lastKeyCheckTime = 0;
int lastKeyState = HIGH;
int lastKeyDebounceState = HIGH;

void setup()
{
   Serial.begin(9600);

   pinMode(TELEGRAPH_KEY_PIN, INPUT_PULLUP);
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
   // check button
   if (millis() + KEY_DEBOUNCE_MILLIS >= lastKeyCheckTime)
   {
      lastKeyCheckTime = millis();

      int currentKeyState = digitalRead(TELEGRAPH_KEY_PIN);
      if (currentKeyState == lastKeyDebounceState)
      {
         // we have a stable debounced key state
         if (lastKeyState == currentKeyState)
         {
            // still the same, nothing has changed
         }
         else
         {
            // key state has changed
            lastKeyState = currentKeyState;

            if (currentKeyState == HIGH)
            {
               // PRESSED -> RELEASED
               Serial.println(F("klucz zwolnioniy"));

               digitalWrite(LED_BUILTIN, LOW);

               analogWrite(BUZZER_PIN, 0);
            }
            else
            {
               // RELEASED -> PRESSED
               Serial.println(F("klucz nacisniety"));

               digitalWrite(LED_BUILTIN, HIGH);
               analogWrite(BUZZER_PIN, 128);
            }
         }
      }
      else
      {
         lastKeyDebounceState = currentKeyState;
      }
   }

//   digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
//   delay(1000);                       // wait for a second
//   digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
//   delay(1000);                       // wait for a second
}

bool isButtonPressed()
{

}
