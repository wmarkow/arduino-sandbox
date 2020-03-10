/*
 * GaugeCommand.h
 *
 *  Created on: 1 paü 2019
 *      Author: wmarkowski
 */

#ifndef GAUGECOMMAND_H_
#define GAUGECOMMAND_H_

#include <AbstractCommand.h>

class GaugeCommand : public AbstractCommand {
 private:
  unsigned long lastProcessTime = 0;
  void printUsage(HardwareSerial *serial);
 public:
  const __FlashStringHelper* getName();
  void process(CommandParams *params, HardwareSerial *serial);
  void processBackground(HardwareSerial *serial);
  void reset(uint8_t gaugeNumber);
};



#endif /* GAUGECOMMAND_H_ */
