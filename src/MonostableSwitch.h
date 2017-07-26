/*
 * MonostableSwitch.h
 *
 *  Created on: 25.07.2017
 *      Author: wmarkowski
 */

#ifndef MONOSTABLESWITCH_H_
#define MONOSTABLESWITCH_H_

#include "AbstractSwitch.h"

class MonostableSwitch : public AbstractSwitch
{
protected:
	void (*onSwitchOn)();
	void (*onSwitchOff)();
	void onSwitchOnInternal();
	void onSwitchOffInternal();

public:
	MonostableSwitch(uint8_t pin);
	void setOnSwitchOn(void (*onSwitchOn)());
	void setOnSwitchOff(void (*onSwitchOff)());
};

#endif /* MONOSTABLESWITCH_H_ */
