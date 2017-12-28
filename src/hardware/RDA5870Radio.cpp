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

   RDA5807M::setVolume(newVolume);
}
