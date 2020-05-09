/*
 * DashCommand.h
 *
 *  Created on: 5 pa� 2019
 *      Author: wmarkowski
 */

#ifndef DASHCOMMAND_H_
#define DASHCOMMAND_H_

#include <AbstractCommand.h>

class PantheonDashCommand: public AbstractCommand
{
private:
    void printUsage(HardwareSerial *serial);
public:
    const __FlashStringHelper* getName();
    void process(CommandParams *params, HardwareSerial *serial);
    void processBackground(HardwareSerial *serial);
};

#endif /* DASHCOMMAND_H_ */
