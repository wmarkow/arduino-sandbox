/*
 * PT2314PreAmp.cpp
 *
 *  Created on: 28.12.2017
 *      Author: wmarkowski
 */

#include "PT2314PreAmp.h"

PT2314PreAmp::PT2314PreAmp(PT2314 *pt2314)
{
   this->pt2314 = pt2314;
   this->volume = 0;
   this->inputChannel = 0;
}

void PT2314PreAmp::setVolume(uint8_t newVolume)
{
   if (getVolume() == newVolume)
   {
      return;
   }

   this->volume = newVolume;
   pt2314->volume(newVolume);
}

uint8_t PT2314PreAmp::getVolume()
{
   return volume;
}

void PT2314PreAmp::setInputChannel(uint8_t channel)
{
   this->inputChannel = channel;
   pt2314->channel(channel);
}

uint8_t PT2314PreAmp::getInputChannel()
{
   return inputChannel;
}
