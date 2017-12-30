/*
 * RDA5870Radio.cpp
 *
 *  Created on: 16.10.2017
 *      Author: wmarkowski
 */

#include "RDA5807PreAmp.h"

RDA5807PreAmp::RDA5807PreAmp(RDA5807M* rda)
{
   this->rda = rda;
}
void RDA5807PreAmp::setVolume(uint8_t newVolume)
{
   if (getVolume() == newVolume)
   {
      return;
   }

   // remap from 0...100 to 0...RDA5807M::MAXVOLUME
   uint8_t remapped = map(newVolume, this->MIN_VOLUME, this->MAX_VOLUME, 0,
         rda->MAXVOLUME);
   rda->setVolume(remapped);
}

uint8_t RDA5807PreAmp::getVolume()
{
   // remap from 0...RDA5807M::MAXVOLUME to 0...100
   return map(rda->getVolume(), 0, rda->MAXVOLUME, this->MIN_VOLUME,
         this->MAX_VOLUME);
}

void RDA5807PreAmp::setInputChannel(uint8_t channel)
{
   // nothing to do
}

uint8_t RDA5807PreAmp::getInputChannel()
{
   // nothing to do
}
