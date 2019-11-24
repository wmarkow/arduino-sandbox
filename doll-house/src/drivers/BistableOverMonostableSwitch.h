/*
 * BistableOverMonostableSwitch.h
 *
 *  Created on: 26.07.2017
 *      Author: wmarkowski
 */

#ifndef BISTABLEOVERMONOSTABLESWITCH_H_
#define BISTABLEOVERMONOSTABLESWITCH_H_

#include <stdint.h>
#include "MonostableSwitch.h"

class BistableOverMonostableSwitch: public MonostableSwitch
{
private:
    uint8_t state;

protected:
    void onSwitchOnInternal();
    void onSwitchOffInternal();
    void setStateOn();
    void setStateOff();
    virtual void onSwitchOn();
    virtual void onSwitchOff();

public:
    BistableOverMonostableSwitch(uint8_t pin);
};

#endif /* BISTABLEOVERMONOSTABLESWITCH_H_ */
