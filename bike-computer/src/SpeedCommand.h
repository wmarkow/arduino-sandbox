/*
 * SpeedCommand.h
 *
 *  Created on: 3 paü 2019
 *      Author: wmarkowski
 */

#ifndef SPEEDCOMMAND_H_
#define SPEEDCOMMAND_H_

#include <AbstractCommand.h>

class SpeedCommand: public AbstractCommand
{
public:
    const __FlashStringHelper* getName();
    void process(CommandParams *params, HardwareSerial *serial);
    void processBackground(HardwareSerial *serial);
};

#endif /* SPEEDCOMMAND_H_ */
