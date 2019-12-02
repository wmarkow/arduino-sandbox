/*
 * MonostableSwitch.h
 *
 *  Created on: 25.07.2017
 *      Author: wmarkowski
 */

#ifndef MONOSTABLESWITCH_H_
#define MONOSTABLESWITCH_H_

#include "AbstractSwitch.h"

class MonostableSwitch: public AbstractSwitch
{
protected:
    uint8_t pin;
    virtual void onSwitchOnInternal() = 0;
    virtual void onSwitchOffInternal() = 0;
    int readButtonState();
public:
    MonostableSwitch(uint8_t pin);
    void init();
};

#endif /* MONOSTABLESWITCH_H_ */
