#include "TelegraphKeyDecoder.h"

#define TELEGRAPH_KEY_PIN A5
#define BUZZER_PIN 3
#define KEY_DEBOUNCE_MILLIS 10
#define DEFAULT_FREQUENCY 1000
#define DITS_PER_WORD   50

#define              TKD_STATE_IDLE 0
#define       TKD_STATE_KEY_PRESSED 1
#define TKD_STATE_WAIT_FOR_CHAR_END 2
#define             TKD_STATE_ERROR 5

TelegraphKeyDecoder::TelegraphKeyDecoder() :
      telegraphKey(TELEGRAPH_KEY_PIN)
{
   state = TKD_STATE_IDLE;
}

void TelegraphKeyDecoder::init()
{
   pinMode(LED_BUILTIN, OUTPUT);

   telegraphKey.init();
   telegraphKey.setTelegraphKeyListener(this);
}

void TelegraphKeyDecoder::setWpm(uint8_t wpm)
{
   dotDuration = (1000.0 * 60.0 / (max(1.0f, (float)wpm) * DITS_PER_WORD));
   dashDuration = 3 * dotDuration;
}

void TelegraphKeyDecoder::loop()
{
   telegraphKey.loop();
   switch (state)
   {
      case TKD_STATE_IDLE:
      {
         if (telegraphKey.isPressed())
         {
            lastTimestamp = millis();
            decodedChar = 1;
            state = TKD_STATE_KEY_PRESSED;
         }
         break;
      }
      case TKD_STATE_KEY_PRESSED:
      {
         uint32_t pressDuration = millis() - lastTimestamp;
         if (pressDuration >= 4.0f * dotDuration)
         {
            lastTimestamp = millis();
            state = TKD_STATE_ERROR;
            Serial.println(F("Too long pressed"));

            break;
         }

         if (telegraphKey.isPressed() == false)
         {
            // check for dot
            if (pressDuration < 1.5f * dotDuration)
            {
               // DOT detected
               Serial.print(F("."));
               decodedChar <<= 1;
            }
            else if (pressDuration > 2.0f * dotDuration
                  && pressDuration < 4.0f * dotDuration)
            {
               // DASH detected
               Serial.print(F("-"));
               decodedChar <<= 1;
               decodedChar |= 1;
            }

            lastTimestamp = millis();
            state = TKD_STATE_WAIT_FOR_CHAR_END;
         }

         break;
      }
      case TKD_STATE_WAIT_FOR_CHAR_END:
      {
         if (telegraphKey.isPressed())
         {
            lastTimestamp = millis();
            state = TKD_STATE_KEY_PRESSED;
            break;
         }

         // not pressed
         uint32_t pauseDuration = millis() - lastTimestamp;
         if (pauseDuration >= 3.0f * dotDuration)
         {
            // end of character transmition
            Serial.print(F("detected "));
            Serial.println(decodedChar);

            state = TKD_STATE_IDLE;
         }

         break;
      }
      case TKD_STATE_ERROR:
      {
         if (millis() > lastTimestamp + 1000)
         {
            state = TKD_STATE_IDLE;
         }
         break;
      }
   }
}

void TelegraphKeyDecoder::onTelegraphKeyPressed()
{
   digitalWrite(LED_BUILTIN, HIGH);
   tone(BUZZER_PIN, DEFAULT_FREQUENCY);
}

void TelegraphKeyDecoder::onTelegraphKeyReleased()
{
   digitalWrite(LED_BUILTIN, LOW);
   noTone(BUZZER_PIN);
}
