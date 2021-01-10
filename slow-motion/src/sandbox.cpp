//////////////////////////////////////////////////////////////////////////////
// Zeitlupenrahmen
//
// Adaption des SlowDance-Projekts von Jeff Liebermann
//
// Der Magnet muss an den Pin 3 und der LED-Stripe an den Pin 10 angeschlossen werden. Nicht verändern!!!
//
// Ulrich Schmerold
// 12/2017
//
// Code und Schaltung sind abgeleitet von:
// TimeFrame V3.0
// Copyright (C) 2016 Cubc-Print
// get the latest source core here: http://www.github.com/cubic-print/timeframe
// video: http://youtu.be/LlGywKkifcI
// order your DIY kit here: http://www.cubic-print.com/TimeFrame
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    GNU General Public License terms: <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>

#define MIN_PHASE_SHIFT -2.0 // minimale Phasenverschiebung (Bewegung rückwärts) in Hz
#define MAX_PHASE_SHIFT 2.0  // maximale Phasenverschiebung (Bewegung vorwärts) in Hz
#define MIN_FREQ 65.0        // minimale Frequenz des Elektromagneten
#define MAX_FREQ 100.0       // maximale Frequenz des Elektromagneten
#define MIN_STRENGTH 5.0     // Mimimalstärke des Elektromagneten
#define MAX_STRENGTH 25.0    // Maximalstärke vom Elektromagneten
#define DUTY_LED 20.0

#define MAGNET_FREQ_INPUT_PIN  A0
#define PHASE_SHIFT_INPUT_PIN  A1
#define MAGNET_DUTY_INPUT_PIN  A2
#define MAGNET_OUTPUT_PIN       3
#define LED_OUTPUT_PIN         10

void Set_Register();
int readMagnetFrequency();
int readPhaseShift();
int readMagnetDuty();

void setup() {
  pinMode(MAGNET_FREQ_INPUT_PIN, INPUT); // Frequenz Elektromagnet
  pinMode(PHASE_SHIFT_INPUT_PIN, INPUT); // Phasenverschiebung (Time Shift)
  pinMode(MAGNET_DUTY_INPUT_PIN, INPUT); // Anzugdauer des Magneten
  pinMode(MAGNET_OUTPUT_PIN, OUTPUT); // Pin 3 als Output (Elektromagnet)
  pinMode(LED_OUTPUT_PIN, OUTPUT);// Pin 10 als Output (LED-Stripe)

  Set_Register();
}

void loop() {

  // Hier wird aus dem Analogwert A1 und oben definierten Grenzen die Phasenverschiebung errechnet.
  float phase_shift = (MAX_PHASE_SHIFT - MIN_PHASE_SHIFT) / 1023 * readPhaseShift() - MAX_PHASE_SHIFT;

  // Hier wird aus dem Analogwert A0 und den oben definierten Grenzen die Elektromagnet-Frequenz errechnet.
  float  frequenz_mag = (MAX_FREQ - MIN_FREQ) / 1023 * readMagnetFrequency() + MIN_FREQ;

  // Fehlt noch die Anzugdauer des Elektromagneten, die aus A2 beerechnet wird.
  float duty_mag = MAX_STRENGTH -(MAX_STRENGTH - MIN_STRENGTH) / 1023 * readMagnetDuty();

  // Die Frequenz der LED errechnet sich aus der Magnetfrequenz und der Phasenverschiebung.
  float frequency_led = frequenz_mag + phase_shift;

  long time_mag = round(16000000 / 1024 / frequenz_mag);
  long time_led = round(16000000 / 64 / frequency_led);

  OCR2A = round(time_mag);                   // Setzen des Output Compare Register vom Timer2
  OCR2B = round(duty_mag * time_mag / 100); // Setzen des duty cycle vom Timer2
  OCR1A = round(time_led);                   // Setzen des Output Compare Register vom Timer1
  OCR1B = round(DUTY_LED * time_led / 100); // Setzen des duty cycle vom Timer1

}

int readMagnetFrequency() {
  return analogRead(MAGNET_FREQ_INPUT_PIN);
//   return 512;
}

int readPhaseShift() {
//  return analogRead(PHASE_SHIFT_INPUT_PIN);
   return analogRead(MAGNET_DUTY_INPUT_PIN);
//   return 512;
}

int readMagnetDuty() {
//  return analogRead(MAGNET_DUTY_INPUT_PIN);
   return 512;
}

void Set_Register() {
  // Die folgenden Zeilen richten die Timer für unsere Zwecke ein.
  // Dazu werden schnelles PWM, der Wellenformerzeugungsmodus und die Prescaler gesetzt.
  // Näheres dazu: https://www.arduino.cc/en/Tutorial/SecretsOfArduinoPWM

  //   WGM = 0b111 Fast PWM (TOP=OCRA)
  // COM2A = 0b01 Toggle OC2A on compare match
  // COM2B = 0b01 Toggle OC2B on compare match
  //   CS2 = 0b111 Clock prescaler 1024
  // With this config the smallest frequency is 16000000/1024/(1 + 255) = 61 Hz
  TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS22)| _BV(CS21)| _BV(CS20);

  //   WGM = 0b1111 Fast PWM (TOP=OCR1A)
  // COM1A = 0b01
  // COM1B = 0b10
  //   CS1 = 0b011 Clock prescaler 64
  // With this config the smallest frequency is 16000000/64/(1 + 65535) = 4 Hz
  TCCR1A = _BV(COM1A0) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
  TCCR1B =  _BV(WGM13) | _BV(WGM12)  |  _BV(CS11) |  _BV(CS10);
}



