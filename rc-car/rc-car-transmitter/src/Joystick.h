/*
 * Joystick.h
 *
 *  Created on: 31 lip 2019
 *      Author: Witold Markowski
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <stdint.h>

class Joystick
{
public:
    Joystick(uint8_t analogPinX, uint8_t analogPinY);
    int16_t readX();
    int16_t readY();
    void setReverseY(bool reverseY);
    void setZeroValueThreshold(uint8_t threshold);
private:
    uint8_t analogPinX;
    uint8_t analogPinY;
    bool reverseY;
    uint8_t zeroValueThreshold;
};



#endif /* JOYSTICK_H_ */
