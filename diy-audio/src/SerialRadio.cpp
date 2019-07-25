/*
 * SerialRadio.cpp
 *
 *  Created on: 24.11.2017
 *      Author: wmarkowski
 */

#include "SerialRadio.h"

RDSParser rds;

SerialRadio::SerialRadio(RADIO* radio)
{
   this->radio = radio;
   state = STATE_PARSECOMMAND;
}
void SerialRadio::init()
{
   radio->attachReceiveRDS(RDS_process);
   rds.init();
   rds.attachServicenNameCallback(DisplayServiceName);
   rds.attachTextCallback(DisplayText);
   rds.attachTimeCallback(DisplayTime);

   runSerialCommand('?', 0);
}

void SerialRadio::loop()
{
   // some internal static values for parsing the input
   static char command;
   static int16_t value;
   char c;
   if (Serial.available() > 0)
   {
      // read the next char from input.
      c = Serial.peek();

      if ((state == STATE_PARSECOMMAND) && (c < 0x20))
      {
         // ignore unprintable chars
         Serial.read();

      }
      else if (state == STATE_PARSECOMMAND)
      {
         // read a command.
         command = Serial.read();
         state = STATE_PARSEINT;

      }
      else if (state == STATE_PARSEINT)
      {
         if ((c >= '0') && (c <= '9'))
         {
            // build up the value.
            c = Serial.read();
            value = (value * 10) + (c - '0');
         }
         else
         {
            // not a value -> execute
            runSerialCommand(command, value);
            command = ' ';
            state = STATE_PARSECOMMAND;
            value = 0;
         } // if
      } // if
   } // if
}

void SerialRadio::runSerialCommand(char cmd, int16_t value)
{
   if (cmd == '?')
   {
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

   else if (cmd == '+')
   {
      // increase volume
      int v = radio->getVolume();
      if (v < 15)
         radio->setVolume(++v);
   }
   else if (cmd == '-')
   {
      // decrease volume
      int v = radio->getVolume();
      if (v > 0)
         radio->setVolume(--v);
   }

   else if (cmd == 'u')
   {
      // toggle mute mode
      radio->setMute(!radio->getMute());
   }

   // toggle stereo mode
   else if (cmd == 's')
   {
      radio->setMono(!radio->getMono());
   }

   // toggle bass boost
   else if (cmd == 'b')
   {
      radio->setBassBoost(!radio->getBassBoost());
   }

   else if (cmd == 'f')
   {
      radio->setFrequency(value);
   }

   else if (cmd == '.')
   {
      radio->seekUp(false);
   }
   else if (cmd == ':')
   {
      radio->seekUp(true);
   }
   else if (cmd == ',')
   {
      radio->seekDown(false);
   }
   else if (cmd == ';')
   {
      radio->seekDown(true);
   }

   // not in help:
   else if (cmd == '!')
   {
      if (value == 0)
         radio->term();
      if (value == 1)
         radio->init();

   }
   else if (cmd == 'i')
   {
      char s[12];
      radio->formatFrequency(s, sizeof(s));
      Serial.print("Station:");
      Serial.println(s);
      Serial.print("Radio:");
      radio->debugRadioInfo();
      Serial.print("Audio:");
      radio->debugAudioInfo();

   } // info

   else if (cmd == 'x')
   {
      radio->debugStatus(); // print chip specific data.
   }
} // runSerialCommand()

void RDS_process(uint16_t block1, uint16_t block2, uint16_t block3,
      uint16_t block4)
{
   rds.processData(block1, block2, block3, block4);
}

/// Update the ServiceName text on the LCD display.
void DisplayServiceName(char *name)
{
   Serial.print("DSN:");
   Serial.println(name);
}

void DisplayText(char *name)
{
   Serial.print("Text:");
   Serial.println(name);
}

void DisplayTime(uint8_t hour, uint8_t minute)
{
   Serial.print("Time:");
   Serial.print(hour);
   Serial.print(":");
   Serial.println(minute);
}
