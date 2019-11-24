/*
 * AbstractSwitch.h
 *
 *  Created on: 26.07.2017
 *      Author: wmarkowski
 */

#ifndef ABSTRACTSWITCH_H_
#define ABSTRACTSWITCH_H_

#define STATE_OFF 0
#define STATE_FIRST_ON 1
#define STATE_ON 2
#define STATE_FIRST_OFF 3

#include <stdint.h>

class AbstractSwitch
{
public:
    AbstractSwitch(uint8_t pin);
    void init();
    void loop();

protected:
    virtual void onSwitchOnInternal() = 0;
    virtual void onSwitchOffInternal() = 0;

private:
    uint8_t pin;
    uint8_t state;
    unsigned long firstTimestamp;
};

#endif /* ABSTRACTSWITCH_H_ */
