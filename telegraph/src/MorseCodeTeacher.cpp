#include "MorseCodeTeacher.h"
#include <LCDKeypadShieldButton.h>

#define                MCT_STATE_IDLE 0
#define        MCT_STATE_ASK_QUESTION 1
#define MCT_STATE_ASK_QUESTION_FINISH 2
#define  MCT_STATE_WAITING_FOR_ANSWER 3

#define BUZZER_PIN 3

MorseCodeTeacher::MorseCodeTeacher(LCDKeypadShield *lcdKeypadShield) :
      speakerMorseSender(BUZZER_PIN)
{
   this->lcdKeypadShield = lcdKeypadShield;
   this->state = MCT_STATE_IDLE;
   this->telegraphKeyDecoder.setTelegraphKeyDecoderListener(this);
}

void MorseCodeTeacher::setup()
{
   speakerMorseSender.setup();
   speakerMorseSender.setWPM(9);
   telegraphKeyDecoder.init();
   telegraphKeyDecoder.setWpm(9);
}

void MorseCodeTeacher::loop()
{
   speakerMorseSender.loop();
   telegraphKeyDecoder.loop();

   switch (state)
   {
      case MCT_STATE_IDLE:
      {
         state = MCT_STATE_ASK_QUESTION;
         break;
      }
      case MCT_STATE_ASK_QUESTION:
      {
         // pick a random letter from a to z
         uint8_t rand = random(26);
         askedChar = 'a' + rand;
         // display on LCD
         display(askedChar);

         // beep morse
         speakerMorseSender.send(askedChar);

         state = MCT_STATE_ASK_QUESTION_FINISH;
         break;
      }
      case MCT_STATE_ASK_QUESTION_FINISH:
      {
         if (speakerMorseSender.isBusy())
         {
            break;
         }
         state = MCT_STATE_WAITING_FOR_ANSWER;
         break;
      }
      case MCT_STATE_WAITING_FOR_ANSWER:
      {
         if (getLCDKeypadShieldButton() == BUTTON_RIGHT)
         {
            state = MCT_STATE_ASK_QUESTION;
         }

         break;
      }
   }
}

void MorseCodeTeacher::display(char c)
{
   lcdKeypadShield->clear();
   lcdKeypadShield->home();
   lcdKeypadShield->print(c);

   MorseBitmask bitmask = speakerMorseSender.getMorseBitmask(c);

   if (bitmask == 0)
   {
      return;
   }

   uint8_t bitIndex = 7;

   // look for sentinel
   for (int q = 7; q >= 1; q--)
   {
      if (bitmask & _BV(q))
      {
         bitIndex = q - 1;
         break;
      }
   }

   lcdKeypadShield->print(' ');
   for (int w = bitIndex; w >= 0; w--)
   {
      if (bitmask & _BV(w))
      {
         lcdKeypadShield->print('-');
      }
      else
      {
         lcdKeypadShield->print('.');
      }

      if (w == 0)
      {
         break;
      }
   }
}

void MorseCodeTeacher::onCharDecoded(char c)
{
   if(state != MCT_STATE_WAITING_FOR_ANSWER)
   {
      return;
   }

   if(askedChar == c)
   {
      state = MCT_STATE_ASK_QUESTION;
   } else
   {
      Serial.println(F("error"));
   }
}

void MorseCodeTeacher::onError()
{
   Serial.println(F("error"));
}
