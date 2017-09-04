/*
 * LightDriver.h
 *
 *  Created on: 30.08.2017
 *      Author: wmarkow
 */

#ifndef LIGHTDRIVER_H_
#define LIGHTDRIVER_H_

#include <stdint.h>

class LightDriver
{
public:
	LightDriver(uint8_t pin);
	void init();
	void switchOn();
	void switchOff();
	bool isOn();
	void toggle();
private:
	uint8_t pin;
};



#endif /* LIGHTDRIVER_H_ */
