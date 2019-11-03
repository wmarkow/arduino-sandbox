/*
 * MLX10407.cpp
 *
 *  Created on: 27 wrz 2019
 *      Author: wmarkowski
 */
#include <Arduino.h>
#include "MLX10407.h"

// Use defines for pin definitions instead of const ints
// defines are substituded at the precompile stage so
// they use no RAM on your device.
#define _MLX_RST_PIN        8
#define _MLX_START_BIT      0x80   // Prefixes all gauge updates

const byte gauge_lookup[6] =
{ 0x00, 0x10, 0x30, 0x40, 0x60, 0x50 };

/***
 * Constructor.
 *
 * @param csPin the number of chip select pin
 */
MLX10407::MLX10407(uint8_t csPin)
{
    this->csPin = csPin;
}

/***
 * Prepares the driver to work.
 * In particular:
 * <ul>
 * </li>configures CS pin</li>
 * </li>configures Reset pin</li>
 * </li>configures SPI</li>
 * </ul>
 */
void MLX10407::init()
{
    // Don't forget to do this, one some boards the gauges will not respond if you leave it out
    pinMode(csPin, OUTPUT);
    pinMode(_MLX_RST_PIN, OUTPUT);

    // Setup SPI
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV32); // wire SPI clock pin to MLX pin SCLK (1MHz is adequate, 4MHz is fine too)
    digitalWrite(csPin, LOW); // MLX expects CS to go high on transfer then low to latch them the bytes in
    digitalWrite(_MLX_RST_PIN, HIGH); // Reset has inverted logic and is active low
}

/***
 * Sets an angle value to the specific logo.
 * It supports positive and negative angles.
 *
 * It is not assured in which direction (clockwise or counterclockwise) the needle will go.
 * With air core gauges there is a known issue, that the needle chooses the closest way
 * when moving from start point to the end point.
 *
 * Example:
 * with this coordinate system:
 *       N(90)
 * W(0)          E(180)
 *       S(270)
 * When moving from 0 degree to 270 degree two paths are possible:
 * <ul>
 * <il>a longer path clockwise from 0 to 270</il>
 * <il>a shorter path counterclockwise from 0 to 270</il>
 * </ul>
 * The needle will choose the shorter path, it may be clockwise or counterclockwise,
 * it depends on the gauge construction itself.
 *
 * @param logoNumber from 1 to 5. Logos 1 and 2 are 360 degree actuators. Logos 3 to 5 are 90 degrees actuators.
 * @param angle from -359 to 359
 */
void MLX10407::writeLogo(uint8_t logoNumber, int16_t angle)
{
    angle = angle % 360;
    if (angle < 0)
    {
        angle += 360;
    }
    uint8_t angleQ = angle % 90; // max 7 bits

    uint8_t quadrant;
    if (angle < 90)
    {
        quadrant = 0;
    }
    else if (angle < 180)
    {
        quadrant = 1;
    }
    else if (angle < 270)
    {
        quadrant = 2;
    }
    else if (angle < 360)
    {
        quadrant = 3;
    }

    uint16_t angleValue = map(angleQ, 0, 89, 0, 1023);

    digitalWrite(csPin, HIGH);
    SPI.transfer(
    _MLX_START_BIT | gauge_lookup[logoNumber] | (angleValue >> 6));
    SPI.transfer(((angleValue & 0b00111111) << 2) | quadrant);
    digitalWrite(csPin, LOW);
}
