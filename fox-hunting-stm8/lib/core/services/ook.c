
#include <Arduino.h>
#include <stddef.h>
#include "ook.h"
#include "../drivers/si4438.h"

bool ook_init_tx_direct_sync()
{
    // configure GPIO of STM8
    // GPIO1 -> PC3 as input pull up
    pinMode(PC3, INPUT);
    digitalWrite(PC3, HIGH);
    // GPIO0 <- PB4 as output always high (carrier always generated)
    pinMode(PB4, OUTPUT);
    digitalWrite(PB4, HIGH);

    // Uncomment the line below to disable signal generation (we are in direct mode).
    // Note: driving GPIO0 low should not generate the output signal, but I have noticed
    // it's generates anyway, however its power is around 70dB weaker. 
    // digitalWrite(PB4, LOW);

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

    if(doAPI(gpioCmd, sizeof(gpioCmd), NULL, 0) == false)
    {
        return false;
    }

    // configure OOK Tx Synchronous Direct mode
    //   TX_DIRECT_MODE_TYPE[0] = 0b0;   Direct mode operates in synchronous mode, applies to TX only.
    // TX_DIRECT_MODE_GPIO[1:0] = 0b00;  TX direct mode uses GPIO0 as data source.
    //          MOD_SOURCE[1:0] = 0b01;  The modulation is sourced in real-time from a GPIO pin
    //            MOD_TYPE[2:0] = 0b001; OOK
    uint8_t value = 0b00001001;
    if(setProperty(SI44338_PROPERTY_MODEM_MOD_TYPE, value) == false)
    {
        return false;
    }

    return ook_stop_tx();
}

bool ook_start_tx()
{
    return si4438_enter_tx_state();
}

bool ook_stop_tx()
{
    return si4438_enter_ready_state();
}