/*
 * LightSwitch.h
 *
 *  Created on: 04.09.2017
 *      Author: wmarkowski
 */

#ifndef LIGHTSWITCH_H_
#define LIGHTSWITCH_H_

#include "drivers/BistableOverMonostableSwitch.h"
#include "drivers/LightDriver.h"

class LightSwitch: public BistableOverMonostableSwitch
{
private:
    LightDriver lightDriver;
protected:
    void onSwitchOn();
    void onSwitchOff();
public:
    LightSwitch(uint8_t switch_pin, uint8_t light_pin);
    void init();
    void switchOn();
    void switchOff();
};

#endif /* LIGHTSWITCH_H_ */
