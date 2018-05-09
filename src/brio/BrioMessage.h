/*
 * BrioMessage.h
 *
 *  Created on: 08.05.2018
 *      Author: wmarkowski
 */

#ifndef BRIO_BRIOMESSAGE_H_
#define BRIO_BRIOMESSAGE_H_

#include <stdint.h>

#define BRIO_CHANNEL_A 0b00001010
#define BRIO_CHANNEL_B 0b00000101

#define BRIO_COMMAND_FAST_FORWARD 0b00001110
#define BRIO_COMMAND_SLOW_FORWARD 0b00001100
#define         BRIO_COMMAND_STOP 0b00001111
#define     BRIO_COMMAND_BACKWARD 0b00001101
#define BRIO_COMMAND_TOGGLE_LIGHT 0b00000111
#define   BRIO_COMMAND_PLAY_SOUND 0b00001011

struct BrioMessage
{
   uint8_t channel;
   uint8_t command;
};

void brio_message_dump(BrioMessage* brioMessage);

#endif /* BRIO_BRIOMESSAGE_H_ */
