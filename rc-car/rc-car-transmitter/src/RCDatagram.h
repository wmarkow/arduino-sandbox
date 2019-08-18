/*
 * RCDatagram.h
 *
 *  Created on: 1 sie 2019
 *      Author: wmarkowski
 */

#ifndef RCDATAGRAM_H_
#define RCDATAGRAM_H_

#include <stdint.h>

struct RCDatagram
{
    /***
     * Right Y in range from -100 to +100.
     *
     * Positive value means joystick goes up/forward.
     * Negative value means joystick goes down/backward.
     */
    int8_t rightYInPercent;

    /***
     * Right X in range from -100 to +100.
     *
     * Positive value means joystick goes right.
     * Negative value means joystick goes left.
     */
    int8_t rightXInPercent;

    /***
     * The state of the L1 button:
     * 0 - button OFF
     * 1 - button ON
     */
    uint8_t l1Button;
};

#endif /* RCDATAGRAM_H_ */
