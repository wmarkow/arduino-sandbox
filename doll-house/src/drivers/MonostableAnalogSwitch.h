/*
 * MonostableAnalogSwitch.h
 *
 *  Created on: 2 gru 2019
 *      Author: wmarkowski
 */

#ifndef DRIVERS_MONOSTABLEANALOGSWITCH_H_
#define DRIVERS_MONOSTABLEANALOGSWITCH_H_

#include "MonostableSwitch.h"

class MonostableAnalogSwitch: public MonostableSwitch
{
public:
    MonostableAnalogSwitch(uint8_t pin, uint16_t minValue, uint16_t maxValue);
    void init();
protected:
    int readButtonState();
private:
   uint16_t minValue;
   uint16_t maxValue;
};

#endif /* DRIVERS_MONOSTABLEANALOGSWITCH_H_ */
