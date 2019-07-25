#include "LocalTelegraph.h"

#define TELEGRAPH_KEY_PIN 8
#define BUZZER_PIN 3
#define KEY_DEBOUNCE_MILLIS 10
#define DEFAULT_FREQUENCY 1000

LocalTelegraph::LocalTelegraph() :
      telegraphKey(TELEGRAPH_KEY_PIN)
{

}

void LocalTelegraph::init()
{
   pinMode(LED_BUILTIN, OUTPUT);

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
   tone(BUZZER_PIN, DEFAULT_FREQUENCY);
}

void LocalTelegraph::onTelegraphKeyReleased()
{
   Serial.println(F("klucz zwolniony"));

   digitalWrite(LED_BUILTIN, LOW);
   noTone(BUZZER_PIN);
}
