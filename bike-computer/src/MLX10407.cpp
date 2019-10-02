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
#define _MLX_RST_PIN        8     // Now wire arduino pin 7 to MLX pin 15
#define _MLX_START_BIT      0x80   // Prefixes all gauge updates

const byte gauge_lookup[6] =
{ 0x10, 0x30, 0x40, 0x60, 0x50 };

MLX10407::MLX10407(uint8_t csPin)
{
    this->csPin = csPin;
}

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
 * Normally for a multibyte transfer you would do SPI.transfer(b1, SPI_CONTINUE);
 * then SPI.transfer(b2); However, since MLX is not really using SPI, the original
 * version does work. However, for good form I am including the change.
 * gaugeNumber should be 1 through 5 ( can make it zero based by removing first
 * element of gauge_lookup array definition above.)
 *
 * @param - gaugeNumber from 0 to 4
 * @param - newValue a value from 0 to 2047
 */
//void MLX10407::setGauge(uint8_t gaugeNumber, uint16_t newValue)
//{
//    uint8_t value = newValue % 512; // This will produce the quandrant value between 0 and 511
//
//    digitalWrite(_MLX_CS_PIN, HIGH);
//    SPI.transfer(_MLX_START_BIT | gauge_lookup[gaugeNumber] | (value >> 5)); //, SPI_CONTINUE);
//    SPI.transfer(value << 3 | (newValue / 512));
//    digitalWrite(_MLX_CS_PIN, LOW);
//}
/***
 * @param - gaugeNumber from 0 to 4
 * @param - newValue from 0 to 359
 */
void MLX10407::setGauge(uint8_t gaugeNumber, uint16_t angle)
{
    angle = angle % 360;
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
//    Serial.println(quadrant);

    uint16_t angleValue = map(angleQ, 0, 89, 0, 1023);
//    Serial.println(angleValue);

    digitalWrite(csPin, HIGH);
    SPI.transfer(
            _MLX_START_BIT | gauge_lookup[gaugeNumber] | (angleValue >> 6));
    SPI.transfer(((angleValue & 0b00111111) << 2) | quadrant);
    digitalWrite(csPin, LOW);
}
