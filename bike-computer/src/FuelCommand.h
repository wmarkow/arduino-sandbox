/*
 * FuelCommand.h
 *
 *  Created on: 3 paü 2019
 *      Author: wmarkowski
 */

#ifndef FUELCOMMAND_H_
#define FUELCOMMAND_H_


#include <AbstractCommand.h>

class FuelCommand: public AbstractCommand
{
public:
    const __FlashStringHelper* getName();
    void process(CommandParams *params, HardwareSerial *serial);
    void processBackground(HardwareSerial *serial);
};

#endif /* FUELCOMMAND_H_ */
