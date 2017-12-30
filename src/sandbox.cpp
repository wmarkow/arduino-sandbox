#include <Wire.h>
#include <RDSParser.h>
#include <LiquidCrystal_I2C.h>
#include <BigCrystal.h>
#include <PT2314.h>

#include "Arduino.h"
#include "hardware/AnalogMonostableSwitch.h"
#include "hardware/PreAmpControlPanel.h"
#include "SerialRadio.h"
#include "hardware/PT2314PreAmp.h"
#include "hardware/RDA5807PreAmp.h"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);
BigCrystal bigLcd(&lcd);

// hardware objects
RDA5807M radio;
PT2314 pt2314;

// preamplifiers
//RDA5807PreAmp rdaPreAmp(&radio);
PT2314PreAmp pt2314PreAmp(&pt2314);

PreAmpControlPanel preAmpControlPanel(&pt2314PreAmp);
//PreAmpControlPanel preAmpControlPanel(&radio);

SerialRadio serialRadio(&radio);
AnalogMonostableSwitch lcdKeypadLeft(0, 0, 50);
AnalogMonostableSwitch lcdKeypadRight(0, 475, 525);

unsigned long lastDisplayUpdateTime = 0;
unsigned long lastRdsCheckTime = 0;

void updateDisplay()
{
   lcd.setCursor(18, 2);

   uint8_t volume = preAmpControlPanel.getPreAmp()->getVolume();
   char vol[3];
   itoa(volume, vol, 10);
   if (volume <= 9)
   {
      bigLcd.setCursor(14, 2);
      bigLcd.print(F("   "));
      bigLcd.setCursor(14, 3);
      bigLcd.print(F("   "));
      bigLcd.printBig(vol, 17, 2);
   }
   else
   {
      bigLcd.printBig(vol, 14, 2);
   }

   lcd.setCursor(6, 0);

   char freq[11];
   radio.getFrequency(); // need to call it to get the current frequency from the chip
   radio.formatFrequency(freq, 11);
   bigLcd.print(freq);

   // display the input channel
   bigLcd.setCursor(0, 3);
   uint8_t channel = preAmpControlPanel.getPreAmp()->getInputChannel();
   if (channel == 0)
   {
      bigLcd.print(F("Radio   "));
   }
   if (channel == 1)
   {
      bigLcd.print(F("Gramofon"));
   }
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

void setup()
{
   Serial.begin(57600);

   bigLcd.begin(20, 4);
   bigLcd.setAppendExtraSpaceBetweenCharacters(false);
   lcd.home();
   lcd.clear();
   lcd.backlight();
   lcd.setBacklightPin(3, POSITIVE);
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
   for (q = 0; q < 20; q++)
   {
      res = pt2314.init();
      if (res == true)
      {
         break;
      }
      delay(100);
   }

   pt2314.channel(0);
   pt2314.volume(1);
   pt2314.attenuation(100, 100);
   pt2314.gain(1);

   radio.init();
   radio.debugEnable();
   radio.setMono(false);
   radio.setMute(false);
   radio.setVolume(15);

   radio.setFrequency(9300);
   serialRadio.init();

   lcd.clear();
   updateDisplay();
}

void loop()
{
   lcdKeypadRight.loop();
   lcdKeypadLeft.loop();

   if (millis() - lastDisplayUpdateTime > 250)
   {
      updateDisplay();
      preAmpControlPanel.loop();
      lastDisplayUpdateTime = millis();
   }

   radio.checkRDS();

   serialRadio.loop();
}
