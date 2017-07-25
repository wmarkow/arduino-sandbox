/*
 * MonostableSwitch.h
 *
 *  Created on: 25.07.2017
 *      Author: wmarkowski
 */

#ifndef MONOSTABLESWITCH_H_
#define MONOSTABLESWITCH_H_

#include <stdint.h>

#define STATE_OFF 0
#define STATE_FIRST_ON 1
#define STATE_ON 2
#define STATE_FIRST_OFF 3

class MonostableSwitch
{
private:
	uint8_t pin;
	uint8_t state;
	unsigned long firstTimestamp;
	void (*onSwitchOn)();
public:
	MonostableSwitch(uint8_t pin);
	void setOnSwitchOn(void (*onSwitchOn)());
	void loop();
	bool isOn();
};



#endif /* MONOSTABLESWITCH_H_ */
