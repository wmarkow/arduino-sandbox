
#include <Wire.h>
#include <RDSParser.h>
#include <LiquidCrystal_I2C.h>
#include <BigCrystal.h>

#include "Arduino.h"
#include "hardware/RDA5870Radio.h"
#include "hardware/AnalogMonostableSwitch.h"

#define VOLUME_ANALOG_INPUT A1

//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);
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

/// State definition for this radio implementation.
enum RADIO_STATE {
  STATE_PARSECOMMAND, ///< waiting for a new command character.

  STATE_PARSEINT,     ///< waiting for digits for the parameter.
  STATE_EXEC          ///< executing the command.
};

RADIO_STATE state; ///< The state variable is used for parsing input characters.

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

	lcd.setCursor(0, 0);

	char freq[11];
	radio.getFrequency(); // need to call it to get the current frequency from the chip
	radio.formatFrequency(freq, 11);
	freq[6] = '\0';
	bigLcd.printBig(freq, 0, 0);
}

void checkVolumePot()
{
	uint16_t volumeInput = analogRead(VOLUME_ANALOG_INPUT);
	uint8_t volume = volumeInput >> 6;

	radio.setVolume(volume);
}

void onLcdKeypadRightPressed()
{
//	Serial.println(F("RIGHT pressed"));
//	radio.seekUp(true);
}

void onLcdKeypadUpPressed()
{
//	Serial.println(F("UP pressed"));
//
//	uint8_t volume = radio.getVolume();
//	volume ++;
//	if(volume >= radio.MAXVOLUME)
//	{
//		radio.setVolume(radio.MAXVOLUME);
//		return;
//	}
//
//	radio.setVolume(volume);
}

void onLcdKeypadDownPressed()
{
//	Serial.println(F("DOWN pressed"));
//
//	uint8_t volume = radio.getVolume();
//	volume --;
//	if(volume >= radio.MAXVOLUME)
//	{
//		radio.setVolume(0);
//		return;
//	}
//
//	radio.setVolume(volume);
}

void onLcdKeypadLeftPressed()
{
//	Serial.println(F("LEFT pressed"));
//	radio.seekDown(true);
}

void onLcdKeypadSelectPressed()
{
	Serial.println(F("SELECT pressed"));
}

void runSerialCommand(char cmd, int16_t value)
{
  if (cmd == '?') {
    Serial.println();
    Serial.println("? Help");
    Serial.println("+ increase volume");
    Serial.println("- decrease volume");
    Serial.println("> next preset");
    Serial.println("< previous preset");
    Serial.println(". scan up   : scan up to next sender");
    Serial.println(", scan down ; scan down to next sender");
    Serial.println("fnnnnn: direct frequency input");
    Serial.println("i station status");
    Serial.println("s mono/stereo mode");
    Serial.println("b bass boost");
    Serial.println("u mute/unmute");
  }

  // ----- control the volume and audio output -----

  else if (cmd == '+') {
    // increase volume
    int v = radio.getVolume();
    if (v < 15) radio.setVolume(++v);
  } else if (cmd == '-') {
    // decrease volume
    int v = radio.getVolume();
    if (v > 0) radio.setVolume(--v);
  }

  else if (cmd == 'u') {
    // toggle mute mode
    radio.setMute(!radio.getMute());
  }

  // toggle stereo mode
  else if (cmd == 's') { radio.setMono(!radio.getMono()); }

  // toggle bass boost
  else if (cmd == 'b') { radio.setBassBoost(!radio.getBassBoost()); }

  else if (cmd == 'f') { radio.setFrequency(value); }

  else if (cmd == '.') { radio.seekUp(false); } else if (cmd == ':') { radio.seekUp(true); } else if (cmd == ',') { radio.seekDown(false); } else if (cmd == ';') { radio.seekDown(true); }


  // not in help:
  else if (cmd == '!') {
    if (value == 0) radio.term();
    if (value == 1) radio.init();

  } else if (cmd == 'i') {
    char s[12];
    radio.formatFrequency(s, sizeof(s));
    Serial.print("Station:"); Serial.println(s);
    Serial.print("Radio:"); radio.debugRadioInfo();
    Serial.print("Audio:"); radio.debugAudioInfo();

  } // info

  else if (cmd == 'x') {
    radio.debugStatus(); // print chip specific data.
  }
} // runSerialCommand()

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
  lcdKeypadUp.init();
  lcdKeypadUp.setOnSwitchOnPtr(&onLcdKeypadUpPressed);
  lcdKeypadDown.init();
  lcdKeypadDown.setOnSwitchOnPtr(&onLcdKeypadDownPressed);
  lcdKeypadLeft.init();
  lcdKeypadLeft.setOnSwitchOnPtr(&onLcdKeypadLeftPressed);
  lcdKeypadSelect.init();
  lcdKeypadSelect.setOnSwitchOnPtr(&onLcdKeypadSelectPressed);

  Serial.begin(57600);
  Serial.print("Radio...");
  delay(500);

  radio.init();
  radio.debugEnable();
  radio.setMono(false);
  radio.setMute(false);
  radio.setVolume(1);
  radio.seekUp(true);

  lcd.clear();
  updateDisplay();

  state = STATE_PARSECOMMAND;
  runSerialCommand('?', 0);
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
	  checkVolumePot();
	  lastDisplayUpdateTime = millis();
  }

  if(millis() - lastRdsCheckTime > 1000)
  {
//    radio.checkRDS();
    lastRdsCheckTime = millis();
  }

  // some internal static values for parsing the input
  static char command;
  static int16_t value;
  char c;
    if (Serial.available() > 0) {
      // read the next char from input.
      c = Serial.peek();

      if ((state == STATE_PARSECOMMAND) && (c < 0x20)) {
        // ignore unprintable chars
        Serial.read();

      } else if (state == STATE_PARSECOMMAND) {
        // read a command.
        command = Serial.read();
        state = STATE_PARSEINT;

      } else if (state == STATE_PARSEINT) {
        if ((c >= '0') && (c <= '9')) {
          // build up the value.
          c = Serial.read();
          value = (value * 10) + (c - '0');
        } else {
          // not a value -> execute
          runSerialCommand(command, value);
          command = ' ';
          state = STATE_PARSECOMMAND;
          value = 0;
        } // if
      } // if
  } // if
}
