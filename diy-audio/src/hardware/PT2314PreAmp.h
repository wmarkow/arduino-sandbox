/*
 * PT2314PreAmp.h
 *
 *  Created on: 28.12.2017
 *      Author: wmarkowski
 */

#ifndef HARDWARE_PT2314PREAMP_H_
#define HARDWARE_PT2314PREAMP_H_

#include "PreAmp.h"
#include <PT2314.h>

class PT2314PreAmp : public PreAmp
{
private:
   PT2314 *pt2314;
   uint8_t volume;
   uint8_t inputChannel;
public:
   PT2314PreAmp(PT2314 *pt2314);
   void setVolume(uint8_t newVolume);
   uint8_t getVolume();
   void setInputChannel(uint8_t channel);
   uint8_t getInputChannel();
};

#endif /* HARDWARE_PT2314PREAMP_H_ */
