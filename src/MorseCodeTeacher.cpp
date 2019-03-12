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
}

void MorseCodeTeacher::setup()
{
   speakerMorseSender.setup();
}

void MorseCodeTeacher::loop()
{
   speakerMorseSender.loop();

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
         char c = 'a' + rand;
         // display on LCD
         display(c);

         // beep morse
         speakerMorseSender.send(c);

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

      if(w == 0)
      {
         break;
      }
   }
}
