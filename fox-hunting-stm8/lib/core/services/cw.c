
#include <Arduino.h>
#include <stddef.h>
#include "cw.h"
#include "../drivers/si4438.h"

bool cw_init_tx_pseudo()
{
    // configure GPIO
    uint8_t gpioCmd[8];
    gpioCmd[0] = SI4438_CMD_GPIO_PIN_CFG;
    gpioCmd[1] = 0x00; // GPIO0
    gpioCmd[2] = 0x00; // GPIO1
    gpioCmd[3] = 0b0000011; // GPIO2: CMOS output driven high, pull up disabled
    gpioCmd[4] = 0b0000010; // GPIO3: CMOS output driven low, pull up disabled
    gpioCmd[5] = 0x00; // NIRQ
    gpioCmd[6] = 0x00; // SDO
    gpioCmd[7] = 0x00; // GEN_CONFIG

    if(doAPI(gpioCmd, sizeof(gpioCmd), NULL, 0) == false)
    {
        return false;
    }

    // configure CW Tx mode
    //   TX_DIRECT_MODE_TYPE[0] = 0b0;   not used as we have PSEUDO mode
    // TX_DIRECT_MODE_GPIO[1:0] = 0b00;  not used as we have PSEUDO mode
    //          MOD_SOURCE[1:0] = 0b10;  PSEUDO. The modulation is sourced from the internal pseudo-random generator.
    //            MOD_TYPE[2:0] = 0b000; CW
    uint8_t value = 0b00010000;
    if(setProperty(SI44338_PROPERTY_MODEM_MOD_TYPE, value) == false)
    {
        return false;
    }

    return cw_stop_tx();
}

bool cw_init_tx_direct()
{
    // configure GPIO of STM8
    // In CW mode entering the Tx state will generate carrier automatically. 
    // Configure both GPIOs as input pull up.
    // GPIO1 -> PC3 as input pull up
    pinMode(PC3, INPUT);
    digitalWrite(PC3, HIGH);
    // GPIO0 <- PB4 as input pull up
    pinMode(PB4, INPUT);
    digitalWrite(PB4, HIGH);

    // configure GPIO of Si44xx
    // GPIO0 and GPIO1 are useless in CW mode becuase entering the Tx state will generate carrier automatically.
    // GPIO2 and GPIO3 drives the RF switch. Here is the table matrix:
    // GPIO2 | GPIO3
    // HIGH  | LOW   RF switch in Tx mode
    // LOW   | HIGH  RF switch in Rx mode
    // HIGH  | HIGH  undefined state
    // LOW   | LOW   undefined state
    // Note: when the chip is in Tx mode but the RF switch is in Rx, the signal 
    // will be transmitted anyway but its power will be around 20dB weaker.
    // See the doc folder for HC-12 schematic and the RF switch manual.
    uint8_t gpioCmd[8];
    gpioCmd[0] = SI4438_CMD_GPIO_PIN_CFG;
    gpioCmd[1] = 0b00000001; // GPIO0: TRISTATE Input and output drivers disabled.
    gpioCmd[2] = 0b00000001; // GPIO1: TRISTATE Input and output drivers disabled.
    gpioCmd[3] = 0b00000011; // GPIO2: CMOS output driven high, pull up disabled. Sets the RF switch into TX mode.
    gpioCmd[4] = 0b00000010; // GPIO3: CMOS output driven low, pull up disabled. Sets the RF switch into TX mode.
    gpioCmd[5] = 0x00; // NIRQ
    gpioCmd[6] = 0x00; // SDO
    gpioCmd[7] = 0x00; // GEN_CONFIG

    if(doAPI(gpioCmd, sizeof(gpioCmd), NULL, 0) == false)
    {
        return false;
    }

    // configure CW Tx Synchronous Direct mode
    //   TX_DIRECT_MODE_TYPE[0] = 0b0;   Direct mode operates in synchronous mode, applies to TX only.
    // TX_DIRECT_MODE_GPIO[1:0] = 0b00;  TX direct mode uses GPIO0 as data source.
    //          MOD_SOURCE[1:0] = 0b01;  The modulation is sourced in real-time from a GPIO pin
    //            MOD_TYPE[2:0] = 0b000; CW
    uint8_t value = 0b00001000;
    if(setProperty(SI44338_PROPERTY_MODEM_MOD_TYPE, value) == false)
    {
        return false;
    }

    return cw_stop_tx();
}

bool cw_start_tx()
{
    return si4438_enter_tx_state();
}

bool cw_stop_tx()
{
    return si4438_enter_ready_state();
}