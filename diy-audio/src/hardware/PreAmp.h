/*
 * PreAmp.h
 *
 *  Created on: 16.10.2017
 *      Author: wmarkowski
 */

#ifndef HARDWARE_PREAMP_H_
#define HARDWARE_PREAMP_H_

#include <stdint.h>

class PreAmp
{
public:
   const uint8_t MIN_VOLUME = 0;
   const uint8_t MAX_VOLUME = 100;
   /***
    * Set volume as a value between 0 and 100
    */
   void virtual setVolume(uint8_t newVolume) = 0;

   /***
    * Get volume as a value between 0 and 100
    */
   uint8_t virtual getVolume() = 0;

   /***
    * Set input channel as a value between 0 and 3
    */
   void virtual setInputChannel(uint8_t channel) = 0;

   /***
    * Get input channel as a value between 0 and 3
    */
   uint8_t virtual getInputChannel() = 0;
};

#endif /* HARDWARE_PREAMP_H_ */
