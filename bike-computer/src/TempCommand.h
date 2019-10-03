/*
 * TempCommand.h
 *
 *  Created on: 3 paü 2019
 *      Author: wmarkowski
 */

#ifndef TEMPCOMMAND_H_
#define TEMPCOMMAND_H_

#include <AbstractCommand.h>

class TempCommand: public AbstractCommand
{
public:
    const __FlashStringHelper* getName();
    void process(CommandParams *params, HardwareSerial *serial);
    void processBackground(HardwareSerial *serial);
};

#endif /* TEMPCOMMAND_H_ */
