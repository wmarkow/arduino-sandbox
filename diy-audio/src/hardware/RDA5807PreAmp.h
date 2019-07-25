/*
 * RDA5870Radio.h
 *
 *  Created on: 16.10.2017
 *      Author: wmarkowski
 */

#ifndef HARDWARE_RDA5807PREAMP_H_
#define HARDWARE_RDA5807PREAMP_H_

#include <RDA5807M.h>
#include "PreAmp.h"

class RDA5807PreAmp : public PreAmp
{
private:
   RDA5807M* rda;
public:
   RDA5807PreAmp(RDA5807M* rda);
   void setVolume(uint8_t newVolume);
   uint8_t getVolume();
   void setInputChannel(uint8_t channel);
   uint8_t getInputChannel();
};

#endif /* HARDWARE_RDA5807PREAMP_H_ */
