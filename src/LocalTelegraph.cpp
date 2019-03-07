#include "LocalTelegraph.h"

#define TELEGRAPH_KEY_PIN 8
#define BUZZER_PIN 3
#define KEY_DEBOUNCE_MILLIS 10

LocalTelegraph::LocalTelegraph() :
      telegraphKey(TELEGRAPH_KEY_PIN)
{

}

void LocalTelegraph::init()
{
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(BUZZER_PIN, OUTPUT);

   telegraphKey.init();
   telegraphKey.setTelegraphKeyListener(this);
}

void LocalTelegraph::loop()
{
   telegraphKey.loop();
}

void LocalTelegraph::onTelegraphKeyPressed()
{
   Serial.println(F("klucz nacisniety"));

   digitalWrite(LED_BUILTIN, HIGH);
   analogWrite(BUZZER_PIN, 128);
}

void LocalTelegraph::onTelegraphKeyReleased()
{
   Serial.println(F("klucz zwolnioniy"));

   digitalWrite(LED_BUILTIN, LOW);
   analogWrite(BUZZER_PIN, 0);
}
