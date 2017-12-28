/*
 * RDA5870Radio.h
 *
 *  Created on: 16.10.2017
 *      Author: wmarkowski
 */

#ifndef HARDWARE_RDA5870RADIO_H_
#define HARDWARE_RDA5870RADIO_H_

#include <RDA5807M.h>
#include "PreAmp.h"

class RDA5807Radio : public RDA5807M, public PreAmp
{

public:
   void setVolume(uint8_t newVolume);
   uint8_t getVolume();
};

#endif /* HARDWARE_RDA5870RADIO_H_ */
