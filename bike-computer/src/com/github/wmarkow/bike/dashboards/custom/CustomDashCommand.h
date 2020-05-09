/*
 * CustomDashCommand.h
 *
 *  Created on: 9 maj 2020
 *      Author: wmarkowski
 */

#ifndef COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_CUSTOMDASHCOMMAND_H_
#define COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_CUSTOMDASHCOMMAND_H_

#include <AbstractCommand.h>

class CustomDashCommand : public AbstractCommand
{
private:
   void printUsage(HardwareSerial *serial);
public:
   const __FlashStringHelper* getName();
   void process(CommandParams *params, HardwareSerial *serial);
   void processBackground(HardwareSerial *serial);
};

#endif /* COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_CUSTOMDASHCOMMAND_H_ */
