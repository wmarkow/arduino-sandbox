#include <stdbool.h>

/*
 * Initiates the fake F3E mode. In this mode a random data are generated by the internal pseudo-random generator.
 * Modulation type is 2FSK, where two different frequencies are used so the generated stream will be hearable
 * on PMR 446 FM receiver.
 */
bool fake_f3e_init_tx_pseudo_sync_2fsk();

/*
 * Initiates the fake F3E mode. In this mode fake_f3e_tone(uint16_t, unsigned long) must be called to generate an FM tone.
 * Modulation type is 2FSK, where two different frequencies are used so the generated stream will be hearable
 * on PMR 446 FM receiver.
 */
bool fake_f3e_init_tx_direct_sync_2fsk();

/*
 * Initiates the fake F3E mode. In this mode fake_f3e_tone(uint16_t, unsigned long) must be called to generate an FM tone.
 * Modulation type is 2GFSK, where two different frequencies are used so the generated stream will be hearable
 * on PMR 446 FM receiver.
 */
bool fake_f3e_init_tx_direct_sync_2gfsk();

/*
 * Starts the fake F3E transmition on specific channel.
 */
bool fake_f3e_start_tx(uint8_t channel);

/*
 * Stops the fake F3E transmition.
 */
bool fake_f3e_stop_tx();

bool fake_f3e_tone(uint16_t freqHz, unsigned long durationUs);

bool fake_f3e_send_aprs_byte(char byte);
