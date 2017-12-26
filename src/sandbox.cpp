
#include <Wire.h>
#include <RDSParser.h>
#include <LiquidCrystal_I2C.h>
#include <BigCrystal.h>
#include <PT2314.h>

#include "Arduino.h"
#include "hardware/RDA5870Radio.h"
#include "hardware/AnalogMonostableSwitch.h"
#include "SerialRadio.h"

#define VOLUME_ANALOG_INPUT A1

//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);
BigCrystal bigLcd(&lcd);

RDA5807Radio radio;
PreAmp *preAmp;
PT2314 pt2314;
SerialRadio serialRadio(&radio);
AnalogMonostableSwitch lcdKeypadLeft(0, 0, 50);
AnalogMonostableSwitch lcdKeypadRight(0, 475, 525);

unsigned long lastDisplayUpdateTime = 0;
unsigned long lastRdsCheckTime = 0;

void updateDisplay()
{
	lcd.setCursor(18, 2);

	uint8_t volume = radio.getVolume();
	char vol[3];
	itoa(volume, vol, 10);
	if(volume <= 9){
		bigLcd.setCursor(14, 2);
		bigLcd.print(F("   "));
		bigLcd.setCursor(14, 3);
		bigLcd.print(F("   "));
		bigLcd.printBig(vol, 17, 2);
	} else {
		bigLcd.printBig(vol, 14, 2);
	}

	lcd.setCursor(6, 0);

	char freq[11];
	radio.getFrequency(); // need to call it to get the current frequency from the chip
	radio.formatFrequency(freq, 11);
	bigLcd.print(freq);
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
	Serial.begin(57600);

//		Serial.println ();
//		Serial.println ("I2C scanner. Scanning ...");
//		byte count = 0;
//		Wire.begin();
//		for (byte i = 1; i < 120; i++)
//		{
//			Wire.beginTransmission (i);
//			if (Wire.endTransmission () == 0)
//			{
//				Serial.print ("Found address: ");
//				Serial.print (i, DEC);
//				Serial.print (" (0x");
//				Serial.print (i, HEX);
//				Serial.println (")");
//				count++;
//				delay (1);  // maybe unneeded?
//			}
//		}
//		Serial.println ("Done.");
//		Serial.print ("Found ");
//		Serial.print (count, DEC);
//		Serial.println (" device(s).");

//  lcd.init(); // I need to call this with my 40x4 LCD
  bigLcd.begin(20, 4);
  bigLcd.setAppendExtraSpaceBetweenCharacters(false);
  lcd.home();
  lcd.clear();
  lcd.backlight();
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.print("Uruchamianie...");

  lcdKeypadRight.init();
  lcdKeypadRight.setOnSwitchOnPtr(&onLcdKeypadRightPressed);
  lcdKeypadLeft.init();
  lcdKeypadLeft.setOnSwitchOnPtr(&onLcdKeypadLeftPressed);

  Serial.begin(57600);
  Serial.print("Radio...");
  delay(500);

  uint8_t q = 0;
  bool res = false;
  for (q = 0 ; q < 20 ; q ++)
  {
	  res = pt2314.init();
	  if(res == true)
	  {
		  break;
	  }
	  delay(100);
  }

  pt2314.channel(0);
  pt2314.volume(100);
  pt2314.attenuation(100,100);
  pt2314.gain(0);

  radio.init();
  radio.debugEnable();
  radio.setMono(false);
  radio.setMute(false);
  radio.setVolume(1);

//  radio.seekUp(true);
  radio.setFrequency(9300);
  serialRadio.init();

  lcd.clear();
  updateDisplay();
}

void loop() {
  lcdKeypadRight.loop();
  lcdKeypadLeft.loop();

  if(millis() - lastDisplayUpdateTime > 250)
  {
	  updateDisplay();
	  checkVolumePot();
	  lastDisplayUpdateTime = millis();
  }

//  if(millis() - lastRdsCheckTime > 1000)
//  {
    radio.checkRDS();
//    lastRdsCheckTime = millis();
//  }

  serialRadio.loop();
}
