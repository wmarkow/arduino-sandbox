#include <Arduino.h>
#include "morse_fake_f3e.h"
#include "../fake_f3e.h"

#define WPM 12

#define DIT_DURATION_MILLIS  (1200 / WPM)   // dot duration in milliseconds
#define DAH_DURATION_MILLIS 3 * DIT_DURATION_MILLIS // dash duration

void morse_fake_f3e_send_word(char* ptr)
{
    while(*ptr != NULL)
    {
        if(*ptr == '.')
        {
            // dit
            morse_fake_f3e_send_dit();
            delay(DIT_DURATION_MILLIS);
        }
        else if(*ptr == ' ')
        {
            // space
            // wait 3 dits, but one dit we've already waited after the last dit or dah...
            // .. so wait just 2 dits
            delay(2 * DIT_DURATION_MILLIS);
        }
        else
        {
            // dah
            morse_fake_f3e_send_dah();
            delay(DIT_DURATION_MILLIS);
        }

        ptr++;
    }

    // wait 7 dits after the sentence, but one dit we've already waited after the last dit or dah...
    // ... so wait just 6 dits
    delay(6 * DIT_DURATION_MILLIS);
}

void inline morse_fake_f3e_send_dit()
{
    fake_f3e_tone(700, ((unsigned long)DIT_DURATION_MILLIS) * ((unsigned long)1000));
}

void inline morse_fake_f3e_send_dah()
{
    fake_f3e_tone(700, ((unsigned long)DAH_DURATION_MILLIS) * ((unsigned long)1000));
}