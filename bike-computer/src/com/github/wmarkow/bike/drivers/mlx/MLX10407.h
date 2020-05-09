/*
 * MLX10407.h
 *
 *  Created on: 27 wrz 2019
 *      Author: wmarkowski
 */

#ifndef MLX10407_H_
#define MLX10407_H_

// SPI is helpful to get MLX10407 working, but not required. It is nice because
// it gives you a serial clock to easily work with and the other pins can be
// helpful but may not be. There are multiple versions of the MLX 10407 data
// sheet out there and some are even erroneous which I suspect is the source
// of most of the issues.

// Here are a couple of other really helpful hints:
// 1: You *really* need +12V connected to MLX pin 1 because if you give it less,
//   say 5V or 9V you will get lazy needle performance and when you set the
//   gauge, for example, to 50 degrees then where the needle falls will be
//   slightly different each time and will greatly depend on if the needle
//   was headed up from a lower angle like 30% or down from a larger angle
//   like 80 degrees.
// 2: Technically you can get away without connecting the ERR pin, but a
//   robus implementation would include and read it. You can probably use MOSI
//   for that. It seems to work OK for me on the Due board.

#include <stdint.h>
#include <SPI.h>

class MLX10407
{
private:
    uint8_t csPin;
public:
    MLX10407();
    MLX10407(uint8_t csPin);
    void init();
    void writeLogo(uint8_t logoNumber, int16_t angle);
};

#endif /* MLX10407_H_ */
