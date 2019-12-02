/*
 * PlaySoundSwitch.h
 *
 *  Created on: 04.09.2017
 *      Author: wmarkow
 */

#ifndef PLAYSOUNDSWITCH_H_
#define PLAYSOUNDSWITCH_H_

#include "drivers/MonostableAnalogSwitch.h"

class PlaySoundSwitch: public MonostableAnalogSwitch
{
private:
    uint8_t onSwitchOnSoundId = 0;
    uint8_t onSwitchOffSoundId = 0;
protected:
    void onSwitchOnInternal();
    void onSwitchOffInternal();
public:
    PlaySoundSwitch(uint8_t pin, uint16_t minValue, uint16_t maxValue);
    void setOnSwitchOnSoundId(uint8_t id);
    void setOnSwitchOffSoundId(uint8_t id);
};

#endif /* PLAYSOUNDSWITCH_H_ */
