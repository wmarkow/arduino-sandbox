#include "Arduino.h"
//The setup function is called once at startup of the sketch
void setup() {
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

	// TOP = 2724, frequency = 5873.7 Hz
	// f = F_CLK / prescaler / (1 + TOP)
	ICR1 = 2723;

	// duty cycle 50%
	OCR1A = 1362;

}

// The loop function is called in an endless loop
void loop() {
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
