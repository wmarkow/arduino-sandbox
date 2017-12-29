/*
 * PreAmpControlPanel.cpp
 *
 *  Created on: 29.12.2017
 *      Author: wmarkowski
 */

#include "PreAmpControlPanel.h"
#include <Arduino.h>

#define VOLUME_ANALOG_INPUT A1

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
}

void PreAmpControlPanel::checkVolumePot()
{
   uint16_t volumeInput = analogRead(VOLUME_ANALOG_INPUT);
   uint8_t volume = map(volumeInput, 0, 1023, preAmp->MIN_VOLUME,
         preAmp->MAX_VOLUME);

   preAmp->setVolume(volume);
}

