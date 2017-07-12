/*
 * Copyright (c) 2016 Evan Kale
 * Media: @EvanKale91
 * Email: EvanKale91@gmail.com
 * Website: www.ISeeDeadPixel.com
 *          www.evankale.blogspot.ca
 *          www.youtube.com/EvanKale91
 *
 * This file is part of ArduinoMetalDetector.
 *
 * ArduinoMetalDetector is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Arduino.h"

// Number of cycles from external counter needed to generate a signal event
#define CYCLES_PER_SIGNAL 2500

// Base tone frequency (speaker)
#define BASE_TONE_FREQUENCY 280

// Frequency delta threshold for fancy spinner to trigger
#define SPINNER_THRESHOLD 700

// Pin definitions
#define SENSITIVITY_POT_APIN 1
#define SPEAKER_PIN 10 // D10
#define SPINNER_PIN 9
#define TRIGGER_BTN_PIN 11
#define RESET_BTN_PIN 12

unsigned long lastSignalTime = 0;
unsigned long signalTimeDelta = 0;

#define BASE_MES_TO_MAKE 8 // the power of 2
#define MES_TO_MAKE BASE_MES_TO_MAKE + 2
uint8_t mesCounter = 0;
unsigned long mesSum = 0;
unsigned long minValue = 1000000;
unsigned long maxValue = 0;

unsigned storedAvgValue = 0;
unsigned long lastStoredAvgValue = 0;
signed long diff = 0;
unsigned long lastPlaySoundMillis = 0;

#define STATE_IDLE 0
#define STATE_METAL 1
uint8_t state = STATE_IDLE;

// This signal is called whenever OCR1A reaches 0
// (Note: OCR1A is decremented on every external clock cycle)
SIGNAL(TIMER1_COMPA_vect)
{
  unsigned long currentTime = micros();
  signalTimeDelta =  currentTime - lastSignalTime;
  lastSignalTime = currentTime;

  mesSum += signalTimeDelta;
  mesCounter ++;
  if(signalTimeDelta < minValue){
	  minValue = signalTimeDelta;
  }

  if(signalTimeDelta > maxValue){
	  maxValue = signalTimeDelta;
    }

  // Reset OCR1A
  OCR1A += CYCLES_PER_SIGNAL;
}

void setup()
{
  // Set WGM(Waveform Generation Mode) to 0 (Normal)
  TCCR1A = 0b00000000;

  // Set CSS(Clock Speed Selection) to 0b111 (External clock source on T0 pin
  // (ie, pin 5 on UNO). Clock on rising edge.)
  TCCR1B = 0b00000111;

  // Enable timer compare interrupt A (ie, SIGNAL(TIMER1_COMPA_VECT))
  TIMSK1 |= (1 << OCIE1A);

  // Set OCR1A (timer A counter) to 1 to trigger interrupt on next cycle
  OCR1A = 1;

  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(SPINNER_PIN, OUTPUT);
  pinMode(TRIGGER_BTN_PIN, INPUT_PULLUP);
  pinMode(RESET_BTN_PIN, INPUT_PULLUP);

  Serial.begin(57600);
}

void playGeiger();
void updateStateAndDiff(signed long diff);

void loop()
{
	playGeiger();

	if(mesCounter == MES_TO_MAKE) {
		mesSum -= minValue;
		mesSum -= maxValue;
		unsigned long average = (mesSum >> 3);
		diff = storedAvgValue - average ;
		Serial.print(average);
		Serial.print(" ");
		Serial.print(minValue);
		Serial.print(" ");
		Serial.print(maxValue);
		Serial.print(" ");
		Serial.print(storedAvgValue);
		Serial.print(" ");
		Serial.print(diff);
		Serial.println();

		if(storedAvgValue == 0){
			storedAvgValue = average;
		}

		updateStateAndDiff(diff);

		unsigned long current = millis();
		if(lastStoredAvgValue == 0 || current - lastStoredAvgValue >= 1500){
			storedAvgValue = average;
			lastStoredAvgValue = current;
		}

		mesCounter = 0;
		mesSum = 0;
		minValue = 1000000;
		maxValue = 0;
	}
}

void playGeiger(){
	if(diff <= 1){
		if(millis() - lastPlaySoundMillis >= 1000){
			tone(SPEAKER_PIN, 1000, 5);

			lastPlaySoundMillis = millis();
		}

		return;
	}

	unsigned long deltaTime = diff * 50;
	if(millis() - lastPlaySoundMillis >= deltaTime){
		tone(SPEAKER_PIN, 1000, 5);

		lastPlaySoundMillis = millis();
	}
}

void updateStateAndDiff(signed long newDiff) {
	if(newDiff < 0){
		newDiff = -newDiff;
	}

	switch(state){
	case STATE_IDLE:
		if(newDiff <= 1){
			state = STATE_IDLE;
		} else {
			state = STATE_METAL;
			lastPlaySoundMillis = 0;
		}
		break;
	case STATE_METAL:
		if(newDiff <= 1){
			state = STATE_IDLE;
		} else {
			state = STATE_METAL;
		}
		break;
	}

	diff = newDiff;
}
