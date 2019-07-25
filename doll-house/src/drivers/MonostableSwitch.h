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
	virtual void onSwitchOnInternal() = 0;
	virtual void onSwitchOffInternal() = 0;

public:
	MonostableSwitch(uint8_t pin);
};

#endif /* MONOSTABLESWITCH_H_ */
