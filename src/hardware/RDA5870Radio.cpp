/*
 * RDA5870Radio.cpp
 *
 *  Created on: 16.10.2017
 *      Author: wmarkowski
 */

#include "RDA5870Radio.h"

void RDA5807Radio::setVolume(uint8_t newVolume)
{
   if (getVolume() == newVolume)
   {
      return;
   }

   // remap from 0...100 to 0...RDA5807M::MAXVOLUME
   uint8_t remapped = map(newVolume, this->MIN_VOLUME, this->MAX_VOLUME, 0,
         RDA5807M::MAXVOLUME);
   RDA5807M::setVolume(remapped);
}

uint8_t RDA5807Radio::getVolume()
{
   // remap from 0...RDA5807M::MAXVOLUME to 0...100
   return map(RDA5807M::getVolume(), 0, RDA5807M::MAXVOLUME, this->MIN_VOLUME,
         this->MAX_VOLUME);
}
