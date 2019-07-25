/*
 * MonostableSwitch.h
 *
 *  Created on: 03.11.2017
 *      Author: wmarkowski
 */

#ifndef HARDWARE_MONOSTABLESWITCH_H_
#define HARDWARE_MONOSTABLESWITCH_H_

#define STATE_OFF 0
#define STATE_FIRST_ON 1
#define STATE_ON 2
#define STATE_FIRST_OFF 3

#include <stdint.h>

class MonostableSwitch
{
public:
   MonostableSwitch(uint8_t pin);
   void init();
   void loop();
   void setOnSwitchOnPtr(void (*onSwitchOnPtr)());
   void setOnSwitchOffPtr(void (*onSwitchOffPtr)());

protected:
   uint8_t pin;
   virtual int readButtonState() = 0;
private:
   uint8_t state;
   unsigned long firstTimestamp;
   void (*onSwitchOnPtr)();
   void (*onSwitchOffPtr)();
};

#endif /* HARDWARE_MONOSTABLESWITCH_H_ */
