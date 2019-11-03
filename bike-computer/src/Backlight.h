/*
 * Backlight.h
 *
 *  Created on: 3 lis 2019
 *      Author: Witold Markowski
 */

#ifndef BACKLIGHT_H_
#define BACKLIGHT_H_

class Backlight
{
public:
    void init();
    void setValuePercent(uint8_t value);
};

#endif /* BACKLIGHT_H_ */
