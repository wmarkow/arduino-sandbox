#include "Arduino.h"
//The setup function is called once at startup of the sketch
void setup()
{
   Serial.begin(57600);

   // set OC1A (D9 / 13) as output
   pinMode(9, OUTPUT);

   // Fast PWM 16bit, TOP=ICR1
   TCCR1B |= (1 << WGM13);
   TCCR1B |= (1 << WGM12);
   TCCR1A |= (1 << WGM11);
   TCCR1A &= ~(1 << WGM10);

   //Clear OC1A on Compare Match, set OC1A at BOTTOM
   TCCR1A |= (1 << COM1A1);
   //	TCCR1A &= ~(1 << COM1A1);
   //	TCCR1A |= (1 << COM1A0);

   // prescaler = 1
   TCCR1B &= ~(1 << CS12);
   TCCR1B &= ~(1 << CS11);
   TCCR1B |= (1 << CS10);

   // TOP = 2723, frequency = 5873.7 Hz
   // f = F_CLK / prescaler / (1 + TOP)
   ICR1 = 2723;
   // duty cycle 50%
   OCR1A = 1362;

   //	// TOP = 5447, frequency = 2936.9 Hz
   //	// f = F_CLK / prescaler / (1 + TOP)
   //	ICR1 = 5447;
   //
   //	// duty cycle 50%
   //	OCR1A = 2724;
   //	// duty cycle 75%: inverted logic after NPN duty cycle goes to 25%
   //	OCR1A = 4086;
   //	// duty cycle 93.75%: inverted logic after NPN duty cycle goes to 6.25%
   //	// can't get lower
   //	OCR1A = 5108;

   //	// TOP = 10895, frequency = 1468.4 Hz
   //	// f = F_CLK / prescaler / (1 + TOP)
   //	ICR1 = 10895;
   //	// duty cycle 50%
   //	OCR1A = 5448;
   //	// duty cycle 75%: inverted logic after NPN duty cycle goes to 25%
   //	OCR1A = 8172;
   //	// duty cycle 96.875%: inverted logic after NPN duty cycle goes to 3.125%
   //	// can't get lower
   //	OCR1A = 10556;
}

// The loop function is called in an endless loop
void loop()
{
   Serial.print("TCCR1B = ");
   Serial.println(TCCR1B);
   Serial.print("TCCR1A = ");
   Serial.println(TCCR1A);
   Serial.print("ICR1 = ");
   Serial.println(ICR1);
   Serial.print("OCR1A = ");
   Serial.println(OCR1A);

   Serial.println("");

   delay(1000);
}
