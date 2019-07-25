/*
 * DigitalMonostableSwitch.h
 *
 *  Created on: 03.11.2017
 *      Author: wmarkowski
 */

#ifndef HARDWARE_DIGITALMONOSTABLESWITCH_H_
#define HARDWARE_DIGITALMONOSTABLESWITCH_H_

#include "MonostableSwitch.h"

class DigitalMonostableSwitch : public MonostableSwitch
{
public:
   DigitalMonostableSwitch(uint8_t pin);

protected:
   int readButtonState();
};

#endif /* HARDWARE_DIGITALMONOSTABLESWITCH_H_ */
