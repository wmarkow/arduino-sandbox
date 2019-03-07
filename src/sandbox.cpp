#include <Arduino.h>
#include "drivers/TelegraphKey.h"

#define TELEGRAPH_KEY_PIN 8
#define BUZZER_PIN 3
#define KEY_DEBOUNCE_MILLIS 10

TelegraphKey telegraphKey(TELEGRAPH_KEY_PIN);

void onTelegraphKeyPressed();
void onTelegraphKeyReleased();

void setup()
{
   Serial.begin(9600);

   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(BUZZER_PIN, OUTPUT);

   telegraphKey.init();
   telegraphKey.setOnKeyPressedCallback(onTelegraphKeyPressed);
   telegraphKey.setOnKeyReleasedCallback(onTelegraphKeyReleased);
}

void loop()
{
   telegraphKey.loop();
}

void onTelegraphKeyPressed()
{
   Serial.println(F("klucz nacisniety"));

   digitalWrite(LED_BUILTIN, HIGH);
   analogWrite(BUZZER_PIN, 128);
}

void onTelegraphKeyReleased()
{
   Serial.println(F("klucz zwolnioniy"));

   digitalWrite(LED_BUILTIN, LOW);
   analogWrite(BUZZER_PIN, 0);
}
