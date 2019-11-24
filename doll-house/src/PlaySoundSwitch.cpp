/*
 * PlaySoundSwitch.cpp
 *
 *  Created on: 04.09.2017
 *      Author: wmarkow
 */
#include <DFRobotDFPlayerMini.h>
#include "PlaySoundSwitch.h"

extern DFRobotDFPlayerMini myDFPlayer;

PlaySoundSwitch::PlaySoundSwitch(uint8_t pin) :
        MonostableSwitch(pin)
{

}

void PlaySoundSwitch::setOnSwitchOnSoundId(uint8_t id)
{
    onSwitchOnSoundId = id;
}

void PlaySoundSwitch::setOnSwitchOffSoundId(uint8_t id)
{
    onSwitchOffSoundId = id;
}

void PlaySoundSwitch::onSwitchOnInternal()
{
    if (onSwitchOnSoundId != 0)
    {
        myDFPlayer.playMp3Folder(onSwitchOnSoundId);
    }
}

void PlaySoundSwitch::onSwitchOffInternal()
{
    if (onSwitchOnSoundId != 0)
    {
        myDFPlayer.playMp3Folder(onSwitchOffSoundId);
    }
}

