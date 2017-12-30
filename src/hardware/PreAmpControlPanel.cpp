/*
 * PreAmpControlPanel.cpp
 *
 *  Created on: 29.12.2017
 *      Author: wmarkowski
 */

#include "PreAmpControlPanel.h"

#include <Arduino.h>
#include <pins_arduino.h>
#include <stdint.h>

#define VOLUME_ANALOG_INPUT A1
#define INPUT_CHANNEL_ANALOG_INPUT A2

PreAmpControlPanel::PreAmpControlPanel(PreAmp *preAmp)
{
   this->preAmp = preAmp;
}

PreAmp* PreAmpControlPanel::getPreAmp()
{
   return preAmp;
}

void PreAmpControlPanel::loop()
{
   checkVolumePot();
   checkInputChannelPot();
}

void PreAmpControlPanel::checkVolumePot()
{
   uint16_t volumeInput = analogRead(VOLUME_ANALOG_INPUT);
   uint8_t volume = map(volumeInput, 0, 1023, preAmp->MIN_VOLUME,
         preAmp->MAX_VOLUME);

   preAmp->setVolume(volume);
}

void PreAmpControlPanel::checkInputChannelPot()
{
   uint16_t volumeInput = analogRead(INPUT_CHANNEL_ANALOG_INPUT);

   uint8_t channel = 0;
   if (volumeInput <= 512)
   {
      channel = 0;
   }
   else if (volumeInput <= 1023)
   {
      channel = 1;
   }

   if (preAmp->getInputChannel() == channel)
   {
      return;
   }

   preAmp->setInputChannel(channel);
}

