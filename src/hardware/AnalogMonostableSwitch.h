/*
 * AnalogMonostableSwitch.h
 *
 *  Created on: 03.11.2017
 *      Author: wmarkowski
 */

#ifndef HARDWARE_ANALOGMONOSTABLESWITCH_H_
#define HARDWARE_ANALOGMONOSTABLESWITCH_H_

#include "MonostableSwitch.h"

class AnalogMonostableSwitch : public MonostableSwitch
{
public:
   AnalogMonostableSwitch(uint8_t pin, uint16_t minValue, uint16_t maxValue);

protected:
   int readButtonState();
private:
   uint16_t minValue;
   uint16_t maxValue;
};

#endif /* HARDWARE_ANALOGMONOSTABLESWITCH_H_ */
