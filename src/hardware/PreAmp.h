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
	void virtual setVolume(uint8_t newVolume) = 0;
};



#endif /* HARDWARE_PREAMP_H_ */
