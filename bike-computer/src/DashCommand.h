/*
 * DashCommand.h
 *
 *  Created on: 5 paü 2019
 *      Author: wmarkowski
 */

#ifndef DASHCOMMAND_H_
#define DASHCOMMAND_H_

#include <AbstractCommand.h>

class DashCommand: public AbstractCommand
{
public:
    const __FlashStringHelper* getName();
    void process(CommandParams *params, HardwareSerial *serial);
    void processBackground(HardwareSerial *serial);
};

#endif /* DASHCOMMAND_H_ */
