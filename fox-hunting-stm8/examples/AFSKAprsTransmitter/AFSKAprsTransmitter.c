#include <Arduino.h>
#include <drivers/si4438.h>
#include <services/modulations/fsk/fsk.h>
#include <services/modulations/afsk/afsk.h>
#include <radio_config_channels.h>

// Basic communication channels are defined in radio_config_channels.h
#define COMMUNICATION_CHANNEL CHANNEL_FOX_0

#define lo8(x) ((x)&0xff)
#define hi8(x) ((x)>>8)

bool chipConnected = false;
unsigned long lastTxStartMillis = 0;
bool isTx = false;

uint16_t crc_ccitt_update(uint16_t crc, uint8_t data);

void setup()
{
    delay(3000);

    Serial_begin(115200);
    si4438_init_hw();
    delay(1000);

    // at first check if the hardware is connected
    Serial_print_s("Si4438 checking hardware...");
    chipConnected = si4438_is_chip_connected();
    if(chipConnected == false)
    {
        Serial_println_s(" failed");
    }
    Serial_println_s(" OK");

    // sending startup config is mandatory (especially POWER_UP which should 
    // be the first command of this config) 
    Serial_print_s("Si4438 apply startup config... ");
    if(si4438_apply_startup_config() == false)
    {
        Serial_println_s(" failed");
    }
    Serial_println_s(" OK");

    // configure the TX power
    Serial_print_s("Si4438 setting TX power...");
    if(si4438_set_tx_power(SI4438_MAX_TX_POWER) == false)
    {
        Serial_println_s(" failed");
    }
    Serial_println_s(" OK");

    // Init fake F3E transmission mode
    Serial_print_s("Si4438 setting FSK mode...");
    if(fsk_init_tx_direct_sync_2fsk() == false)
    {
        Serial_println_s(" failed");
    }
    Serial_println_s(" OK");
}

void loop()
{
    // RS41 sonde sends frame with max 320 bytes
    // The frame which it leads is 320* bytes long and thus counts just over 533 ms


    // Enter the Tx state on channel 0
    fsk_start_tx(COMMUNICATION_CHANNEL);

    char minimalFrame[] = {'S', 'Q', '3', 'E', 'T', ' ', '0', 'S', 'P', '3', 'W', 'A', 'M', '0', 'W', 'I', 'D', 'E', '2', ' ', '2', 0x03, 0xF0, ':', 'B', 'L', 'N', '0', ' ', ' ', ' ', ' ', ' ', ':', 'H', 'e', 'l', 'l', 'o', ' ', 'f', 'r', 'o', 'm', ' ', 'H', 'C', '1', '2', '#', '#'};
    uint8_t frameLength = sizeof(minimalFrame);

    // The SSID in the Destination Address field of all packets is coded to specify
    // the APRS digipeater path. See APRS101.pdf page 15.
    // minimalFrame[6] = 0b00110000; // C=0, RR=11, SSID=0, it uses digipiter "VIA". That's the same as using ASCII of character '0'.
    // minimalFrame[13] = 0b00110000; // C=0, RR=11, SSID=0. That's the same as using ASCII of character '0'.
    // define "VIA" as 'W', 'I', 'D', 'E', '2', ' ' with a correct SSID of 2 (means to use WIDE2-2). 
    // minimalFrame[20] = 0b00110010; // C=0, RR=11, SSID=2. That's the same as using ASCII of character '2'.
    
    // shift address bytes one bit to the left
    for(uint8_t q = 0 ; q < 21 ; q ++)
    {
        minimalFrame[q] = minimalFrame[q] << 1;
    }
    // set the LSB of the last address byte
    minimalFrame[20] |= 0x01;

    // Frame Check Sequence - CRC-16-CCITT (0xFFFF)
    uint16_t crc = 0xFFFF;
    for(uint16_t i = 0; i < frameLength - 2; i++)
    {
        crc = crc_ccitt_update(crc, minimalFrame[i]);
    }
    crc = ~crc;                              // flip the bits
    minimalFrame[frameLength - 2] = crc & 0xFF;           // FCS is sent low-byte first
    minimalFrame[frameLength - 1] = (crc >> 8) & 0xFF;

    // init APRS transmition
    afsk_send_aprs_init();
    // send APRS packet
    afsk_send_aprs_packet(minimalFrame, frameLength);

    // stop transmition
    fsk_stop_tx();
    
    // wait a bit
    delay(10000);
}

uint16_t crc_ccitt_update(uint16_t crc, uint8_t data)
{
	data ^= lo8 (crc);
	data ^= data << 4;
	
	return ((((uint16_t)data << 8) | hi8 (crc)) ^ (uint8_t)(data >> 4) ^ ((uint16_t)data << 3));
}

INTERRUPT_HANDLER(AWU_IRQHandler, ITC_IRQ_AWU)
{

}