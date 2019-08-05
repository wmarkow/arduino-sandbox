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
     * Speed in range from -100 to +100.
     * 0 means that the car should stop.
     * Positive value means that it should go forward.
     * Negative value means that it should go backward.
     */
    int8_t speedInPercent;

    /***
     * Steering angle from -100 to +100.
     * 0 means that the steering should be set straight.
     * Positive value means that the steering should go right.
     * Negative value means that the steering should go left.
     */
    int8_t steeringAngleInPercent;

    /***
     * The state of the turbo button:
     * 0 - button OFF
     * 1 - button ON
     */
    uint8_t turboButtonState;
};

#endif /* RCDATAGRAM_H_ */
