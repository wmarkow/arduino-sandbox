
#include <Wire.h>
#include <RDSParser.h>
#include <LiquidCrystal.h>
#include <BigCrystal.h>

#include "Arduino.h"
#include "hardware/RDA5870Radio.h"
#include "hardware/AnalogMonostableSwitch.h"

#define VOLUME_ANALOG_INPUT A1

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
BigCrystal bigLcd(&lcd);

RDA5807Radio radio;
PreAmp *preAmp;
AnalogMonostableSwitch lcdKeypadRight(0, 0, 50);
AnalogMonostableSwitch lcdKeypadUp(0, 51, 175);
AnalogMonostableSwitch lcdKeypadDown(0, 176, 325);
AnalogMonostableSwitch lcdKeypadLeft(0, 326, 525);
AnalogMonostableSwitch lcdKeypadSelect(0, 526, 775);

unsigned long lastDisplayUpdateTime = 0;
unsigned long lastRdsCheckTime = 0;

void updateDisplay()
{
	lcd.setCursor(14, 0);

	uint8_t volume = radio.getVolume();
	char vol[3];
	itoa(volume, vol, 10);
	if(volume <= 9){
		bigLcd.setCursor(10, 0);
		bigLcd.print(F("   "));
		bigLcd.setCursor(10, 1);
		bigLcd.print(F("   "));
		bigLcd.printBig(vol, 13, 0);
	} else {
		bigLcd.printBig(vol, 10, 0);
	}

	lcd.setCursor(0, 0);

	char freq[11];
	radio.getFrequency(); // need to call it to get the current frequency from the chip
	radio.formatFrequency(freq, 11);
	lcd.print(freq);
}

void checkVolumePot()
{
	uint16_t volumeInput = analogRead(VOLUME_ANALOG_INPUT);
	uint8_t volume = volumeInput >> 6;

	radio.setVolume(volume);
}

void onLcdKeypadRightPressed()
{
	Serial.println(F("RIGHT pressed"));
	radio.seekUp(true);
}

void onLcdKeypadUpPressed()
{
	Serial.println(F("UP pressed"));

	uint8_t volume = radio.getVolume();
	volume ++;
	if(volume >= radio.MAXVOLUME)
	{
		radio.setVolume(radio.MAXVOLUME);
		return;
	}

	radio.setVolume(volume);
}

void onLcdKeypadDownPressed()
{
	Serial.println(F("DOWN pressed"));

	uint8_t volume = radio.getVolume();
	volume --;
	if(volume >= radio.MAXVOLUME)
	{
		radio.setVolume(0);
		return;
	}

	radio.setVolume(volume);
}

void onLcdKeypadLeftPressed()
{
	Serial.println(F("LEFT pressed"));
	radio.seekDown(true);
}

void onLcdKeypadSelectPressed()
{
	Serial.println(F("SELECT pressed"));
}

void setup() {
  lcd.begin(16, 2);

  lcd.print("Uruchamianie...");

  lcdKeypadRight.init();
  lcdKeypadRight.setOnSwitchOnPtr(&onLcdKeypadRightPressed);
  lcdKeypadUp.init();
  lcdKeypadUp.setOnSwitchOnPtr(&onLcdKeypadUpPressed);
  lcdKeypadDown.init();
  lcdKeypadDown.setOnSwitchOnPtr(&onLcdKeypadDownPressed);
  lcdKeypadLeft.init();
  lcdKeypadLeft.setOnSwitchOnPtr(&onLcdKeypadLeftPressed);
  lcdKeypadSelect.init();
  lcdKeypadSelect.setOnSwitchOnPtr(&onLcdKeypadSelectPressed);

  bigLcd.setAppendExtraSpaceBetweenCharacters(false);
  Serial.begin(57600);
  Serial.print("Radio...");
  delay(500);

  radio.init();

  radio.debugEnable();

  radio.setMono(false);
  radio.setMute(false);
  radio.setVolume(1);

  lcd.clear();
  updateDisplay();
}

void loop() {
  lcdKeypadRight.loop();
  lcdKeypadUp.loop();
  lcdKeypadDown.loop();
  lcdKeypadLeft.loop();
  lcdKeypadSelect.loop();

  if(millis() - lastDisplayUpdateTime > 250)
  {
	  updateDisplay();
//	  checkVolumePot();
	  lastDisplayUpdateTime = millis();
  }

  if(millis() - lastRdsCheckTime > 1000)
  {
    radio.checkRDS();
    lastRdsCheckTime = millis();
  }
}
