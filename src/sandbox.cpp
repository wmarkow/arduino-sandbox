///
/// \file SerialRadio.ino
/// \brief Radio implementation using the Serial communication.
///
/// \author Matthias Hertel, http://www.mathertel.de
/// \copyright Copyright (c) 2014 by Matthias Hertel.\n
/// This work is licensed under a BSD style license.\n
/// See http://www.mathertel.de/License.aspx
///
/// \details
/// This is a full function radio implementation that uses a LCD display to show the current station information.\n
/// It can be used with various chips after adjusting the radio object definition.\n
/// Open the Serial console with 57600 baud to see current radio information and change various settings.
///
/// Wiring
/// ------
/// The necessary wiring of the various chips are described in the Testxxx example sketches.
/// The boards have to be connected by using the following connections:
///
/// Arduino port | SI4703 signal | RDA5807M signal
/// :----------: | :-----------: | :-------------:
///          GND | GND           | GND
///         3.3V | VCC           | -
///           5V | -             | VCC
///           A5 | SCLK          | SCLK
///           A4 | SDIO          | SDIO
///           D2 | RST           | -
///
///
/// More documentation and source code is available at http://www.mathertel.de/Arduino
///
/// History:
/// --------
/// * 05.08.2014 created.
/// * 04.10.2014 working.

#include <Wire.h>
#include <RDSParser.h>
#include <LCDKeypadShield.h>

#include "Arduino.h"
#include "hardware/RDA5870Radio.h"
#include "hardware/AnalogMonostableSwitch.h"

#define VOLUME_ANALOG_INPUT A1

LCDKeypadShield lcd(8, 9, 4, 5, 6, 7);

RDA5807Radio radio;
PreAmp *preAmp;
AnalogMonostableSwitch lcdKeypadRight(0, 0, 50);
AnalogMonostableSwitch lcdKeypadUp(0, 51, 175);
AnalogMonostableSwitch lcdKeypadDown(0, 176, 325);
AnalogMonostableSwitch lcdKeypadLeft(0, 326, 525);
AnalogMonostableSwitch lcdKeypadSelect(0, 526, 775);

// Define some stations available at your locations here:
// 89.40 MHz as 8940

RADIO_FREQ preset[] = {
  8770,
  8810, // hr1
  8820,
  8850, // Bayern2
  8890, // ???
  8930, // * hr3
  8980,
  9180,
  9220, 9350,
  9440, // * hr1
  9510, // - Antenne Frankfurt
  9530,
  9560, // Bayern 1
  9680, 9880,
  10020, // planet
  10090, // ffh
  10110, // SWR3
  10030, 10260, 10380, 10400,
  10500 // * FFH
};

int    i_sidx=5;        ///< Start at Station with index=5

/// get a RDS parser
RDSParser rds;


/// State definition for this radio implementation.
enum RADIO_STATE {
  STATE_PARSECOMMAND, ///< waiting for a new command character.

  STATE_PARSEINT,     ///< waiting for digits for the parameter.
  STATE_EXEC          ///< executing the command.
};

RADIO_STATE state; ///< The state variable is used for parsing input characters.
unsigned long lastDisplayUpdateTime = 0;
unsigned long lastRdsCheckTime = 0;

// - - - - - - - - - - - - - - - - - - - - - - - - - -



/// Update the Frequency on the LCD display.
void DisplayFrequency(RADIO_FREQ f)
{
  char s[12];
  radio.formatFrequency(s, sizeof(s));
  Serial.print("FREQ:"); Serial.println(s);
} // DisplayFrequency()


/// Update the ServiceName text on the LCD display.
void DisplayServiceName(char *name)
{
  Serial.print("RDS:");
  Serial.println(name);
} // DisplayServiceName()


// - - - - - - - - - - - - - - - - - - - - - - - - - -


void RDS_process(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4) {
  rds.processData(block1, block2, block3, block4);
}


/// Execute a command identified by a character and an optional number.
/// See the "?" command for available commands.
/// \param cmd The command character.
/// \param value An optional parameter for the command.
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
  }
  else if (cmd == '-') {
    // decrease volume
    int v = radio.getVolume();
    if (v > 0) radio.setVolume(--v);
  }

  else if (cmd == 'u') {
    // toggle mute mode
    radio.setMute(! radio.getMute());
  }

  // toggle stereo mode
  else if (cmd == 's') { radio.setMono(! radio.getMono()); }

  // toggle bass boost
  else if (cmd == 'b') { radio.setBassBoost(! radio.getBassBoost()); }

  // ----- control the frequency -----

  else if (cmd == '>') {
    // next preset
    if (i_sidx < (sizeof(preset) / sizeof(RADIO_FREQ))-1) {
      i_sidx++; radio.setFrequency(preset[i_sidx]);
    } // if
  }
  else if (cmd == '<') {
    // previous preset
    if (i_sidx > 0) {
      i_sidx--;
      radio.setFrequency(preset[i_sidx]);
    } // if

  }
  else if (cmd == 'f') { radio.setFrequency(value); }

  else if (cmd == '.') { radio.seekUp(false); }
  else if (cmd == ':') { radio.seekUp(true); }
  else if (cmd == ',') { radio.seekDown(false); }
  else if (cmd == ';') { radio.seekDown(true); }


  // not in help:
  else if (cmd == '!') {
    if (value == 0) radio.term();
    if (value == 1) radio.init();

  }
  else if (cmd == 'i') {
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

void updateDisplay()
{
	lcd.setCursor(14, 0);

	uint8_t volume = radio.getVolume();
	if(volume <= 9){
		lcd.print(F(" "));
		lcd.print(volume);
	} else {
		lcd.print(volume);
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

/// Setup a FM only radio configuration with I/O for commands and debugging on the Serial port.
void setup() {
	// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
	  // Print a message to the LCD.
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

  // open the Serial port
  Serial.begin(57600);
  Serial.print("Radio...");
  delay(500);

  // Initialize the Radio
  radio.init();

  // Enable information to the Serial port
  radio.debugEnable();

  radio.setBandFrequency(RADIO_BAND_FM, preset[i_sidx]); // 5. preset.

  // delay(100);

  radio.setMono(false);
  radio.setMute(false);
  // radio.debugRegisters();
  radio.setVolume(1);

  Serial.write('>');

  state = STATE_PARSECOMMAND;

  // setup the information chain for RDS data.
  radio.attachReceiveRDS(RDS_process);
  rds.attachServicenNameCallback(DisplayServiceName);

  runSerialCommand('?', 0);

  lcd.clear();
  updateDisplay();
} // Setup


/// Constantly check for serial input commands and trigger command execution.
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
    radio.checkRDS();
    lastRdsCheckTime = millis();
  }


  int newPos;
  unsigned long now = millis();
  static unsigned long nextFreqTime = 0;
  static unsigned long nextRadioInfoTime = 0;

  // some internal static values for parsing the input
  static char command;
  static int16_t value;
  static RADIO_FREQ lastf = 0;
  RADIO_FREQ f = 0;

  char c;
  if (Serial.available() > 0) {
    // read the next char from input.
    c = Serial.peek();

    if ((state == STATE_PARSECOMMAND) && (c < 0x20)) {
      // ignore unprintable chars
      Serial.read();

    }
    else if (state == STATE_PARSECOMMAND) {
      // read a command.
      command = Serial.read();
      state = STATE_PARSEINT;

    }
    else if (state == STATE_PARSEINT) {
      if ((c >= '0') && (c <= '9')) {
        // build up the value.
        c = Serial.read();
        value = (value * 10) + (c - '0');
      }
      else {
        // not a value -> execute
        runSerialCommand(command, value);
        command = ' ';
        state = STATE_PARSECOMMAND;
        value = 0;
      } // if
    } // if
  } // if


  // check for RDS data
//  radio.checkRDS();

  // update the display from time to time
  if (now > nextFreqTime) {
    f = radio.getFrequency();
    if (f != lastf) {
      // print current tuned frequency
      DisplayFrequency(f);
      lastf = f;
    } // if
    nextFreqTime = now + 400;
  } // if

} // loop

// End.
