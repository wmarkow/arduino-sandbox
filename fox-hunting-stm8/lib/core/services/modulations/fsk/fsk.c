#include <Arduino.h>
#include <stddef.h>
#include "fsk.h"
#include "../../../drivers/si4438.h"

bool fsk_init_tx_pseudo_sync_2fsk()
{
    // Configure GPIO of STM8: this is irrelevant for pseudorandom PN9 mode.
    // Configure them as input with pull up enabled.
    // GPIO1 -> PC3 as input pull up
    pinMode(PC3, INPUT);
    digitalWrite(PC3, HIGH);
    // GPIO0 <- PB4 as input pull up
    pinMode(PB4, INPUT);
    digitalWrite(PB4, HIGH);


    // configure GPIO of Si44xx
    // GPIO0 and GPIO1 are useless in PSEUDO mode becuase data are generated by internal pseudo random generator.
    uint8_t gpioCmd[8];
    gpioCmd[0] = SI4438_CMD_GPIO_PIN_CFG;
    gpioCmd[1] = 0b00000001; // GPIO0: TRISTATE Input and output drivers disabled.
    gpioCmd[2] = 0b00000001; // GPIO1: TRISTATE Input and output drivers disabled.
    gpioCmd[3] = 0b00000011; // GPIO2: CMOS output driven high, pull up disabled. Sets the RF switch into TX mode.
    gpioCmd[4] = 0b00000010; // GPIO3: CMOS output driven low, pull up disabled. Sets the RF switch into TX mode.
    gpioCmd[5] = 0x00; // NIRQ
    gpioCmd[6] = 0x00; // SDO
    gpioCmd[7] = 0x00; // GEN_CONFIG

    if(si4438_doAPI(gpioCmd, sizeof(gpioCmd), NULL, 0) == false)
    {
        return false;
    }

    // configure 2FSK Tx Synchronous PSEUDO mode
    //   TX_DIRECT_MODE_TYPE[0] = 0b0;   SYNC Direct mode operates in synchronous mode, applies to TX only.
    // TX_DIRECT_MODE_GPIO[1:0] = 0b00;  GPIO0 TX direct mode uses GPIO0 as data source.
    //          MOD_SOURCE[1:0] = 0b10;  PSEUDO The modulation is sourced from the internal pseudo-random generator.
    //            MOD_TYPE[2:0] = 0b010; 2FSK
    uint8_t value = 0b00010010;
    if(si4438_setProperty(SI44338_PROPERTY_MODEM_MOD_TYPE, value) == false)
    {
        return false;
    }

    return fsk_stop_tx();
}

bool fsk_init_tx_direct_sync_2fsk()
{
    // Configure GPIO of STM8
    // GPIO1 -> PC3 as input pull up
    pinMode(PC3, INPUT);
    digitalWrite(PC3, HIGH);
    // GPIO0 <- PB4 as output
    pinMode(PB4, OUTPUT);
    digitalWrite(PB4, LOW);


    // configure GPIO of Si44xx
    uint8_t gpioCmd[8];
    gpioCmd[0] = SI4438_CMD_GPIO_PIN_CFG;
    gpioCmd[1] = 0b01000100; // GPIO0: INPUT Pin is configured as CMOS input. Pull Up enabled (it's important!).
    gpioCmd[2] = 0b00010000; // GPIO1: TX_DATA_CLK Outputs the TX Data Clock signal. Pull Up disabled.
    gpioCmd[3] = 0b00000011; // GPIO2: CMOS output driven high, pull up disabled. Sets the RF switch into TX mode.
    gpioCmd[4] = 0b00000010; // GPIO3: CMOS output driven low, pull up disabled. Sets the RF switch into TX mode.
    gpioCmd[5] = 0x00; // NIRQ
    gpioCmd[6] = 0x00; // SDO
    gpioCmd[7] = 0x00; // GEN_CONFIG

    if(si4438_doAPI(gpioCmd, sizeof(gpioCmd), NULL, 0) == false)
    {
        return false;
    }

    // configure 2FSK Tx Synchronous DIRECT mode
    //   TX_DIRECT_MODE_TYPE[0] = 0b0;   SYNC Direct mode operates in synchronous mode, applies to TX only.
    // TX_DIRECT_MODE_GPIO[1:0] = 0b00;  GPIO0 TX direct mode uses GPIO0 as data source.
    //          MOD_SOURCE[1:0] = 0b01;  DIRECT The modulation is sourced in real-time from a GPIO pin
    //            MOD_TYPE[2:0] = 0b010; 2FSK
    uint8_t value = 0b00001010;
    if(si4438_setProperty(SI44338_PROPERTY_MODEM_MOD_TYPE, value) == false)
    {
        return false;
    }

    return fsk_stop_tx();
}

bool fsk_init_tx_direct_sync_2gfsk()
{
    // Configure GPIO of STM8
    // GPIO1 -> PC3 as input pull up
    pinMode(PC3, INPUT);
    digitalWrite(PC3, HIGH);
    // GPIO0 <- PB4 as output
    pinMode(PB4, OUTPUT);
    digitalWrite(PB4, LOW);


    // configure GPIO of Si44xx
    uint8_t gpioCmd[8];
    gpioCmd[0] = SI4438_CMD_GPIO_PIN_CFG;
    gpioCmd[1] = 0b01000100; // GPIO0: INPUT Pin is configured as CMOS input. Pull Up enabled (it's important!).
    gpioCmd[2] = 0b00010000; // GPIO1: TX_DATA_CLK Outputs the TX Data Clock signal. Pull Up disabled.
    gpioCmd[3] = 0b00000011; // GPIO2: CMOS output driven high, pull up disabled. Sets the RF switch into TX mode.
    gpioCmd[4] = 0b00000010; // GPIO3: CMOS output driven low, pull up disabled. Sets the RF switch into TX mode.
    gpioCmd[5] = 0x00; // NIRQ
    gpioCmd[6] = 0x00; // SDO
    gpioCmd[7] = 0x00; // GEN_CONFIG

    if(si4438_doAPI(gpioCmd, sizeof(gpioCmd), NULL, 0) == false)
    {
        return false;
    }

    // configure 2FSK Tx Synchronous DIRECT mode
    //   TX_DIRECT_MODE_TYPE[0] = 0b0;   SYNC Direct mode operates in synchronous mode, applies to TX only.
    // TX_DIRECT_MODE_GPIO[1:0] = 0b00;  GPIO0 TX direct mode uses GPIO0 as data source.
    //          MOD_SOURCE[1:0] = 0b01;  DIRECT The modulation is sourced in real-time from a GPIO pin
    //            MOD_TYPE[2:0] = 0b011; 2GFSK
    uint8_t value = 0b00001011;
    if(si4438_setProperty(SI44338_PROPERTY_MODEM_MOD_TYPE, value) == false)
    {
        return false;
    }

    return fsk_stop_tx();
}

bool fsk_start_tx(uint8_t channel)
{
    digitalWrite(PB4, LOW);

    return si4438_enter_tx_state(channel);
}

bool fsk_stop_tx()
{
    digitalWrite(PB4, LOW);

    return si4438_enter_ready_state();
}

inline void fsk_tx_direct_bit_high()
{
    digitalWrite(PB4, HIGH);
}

inline void fsk_tx_direct_bit_low()
{
    digitalWrite(PB4, LOW);
}
