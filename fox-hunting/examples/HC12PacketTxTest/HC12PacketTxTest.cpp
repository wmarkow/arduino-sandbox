#include <Arduino.h>
#include <HC12.h>

const uint16_t DOT_DURATION_MILLIS = 150;
const uint16_t DASH_DURATION_MILLIS = 3 * DOT_DURATION_MILLIS;

HC12 hc12;
char text[100];

void sendBytes(uint8_t count);
uint16_t moeDurationInMillis();

void setup()
{
    Serial.begin(115200);

    if(hc12.begin())
    {
        Serial.println(F("HC12.begin() success"));
    }
    else
    {
        Serial.println(F("HC12.begin() failed"));
    }

    if(hc12.setDefault())
    {
        Serial.println(F("HC12.setDefault() success"));
    }
    else
    {
        Serial.println(F("HC12.setDefault() failed"));
    }

    if(hc12.setTxPowerValue(1) == 0)
    {
        Serial.println("Setting Tx power to -1dBm");
    }
    else
    {
        Serial.println("Setting Tx power failed");
    }

    uint16_t dataRate =  hc12.getAirDataRateInKbs();
    sprintf(text, "dataRate = %d kbps", dataRate);
    Serial.println(text);
}

void loop()
{
    unsigned long startTime = millis();
    unsigned long duration = moeDurationInMillis();
    Serial.println(duration);
    while(millis() < startTime + duration)
    {
        // speed 9600bps
        // 31 Bytes = 31 * 10bits = 310bits
        // 9600bps -> 1sec
        // 310bits -> 0.032s
        // 5 * 50ms = 250ms
        // razem: 32ms + 250ms = 282ms
        sendBytes(1);
        delay(50);

        sendBytes(2);
        delay(50);

        sendBytes(4);
        delay(50);

        sendBytes(8);
        delay(50);

        sendBytes(16);
        delay(50);
        Serial.println(F("P"));
    }
    Serial.println(F("end"));
    delay(1000);
}

/*
 * Writes a specific number of bytes immediately to HC-12 device.
 */
void sendBytes(uint8_t count)
{
    for(uint8_t q = 0 ; q < count ; q ++)
    {
        hc12.write(count);
    }
}

uint16_t moeDurationInMillis()
{
    uint16_t duration = 0;
    // send M
    duration += DASH_DURATION_MILLIS;
    duration += DOT_DURATION_MILLIS;  
    duration += DASH_DURATION_MILLIS;
    duration += 3 * DOT_DURATION_MILLIS;
    
    // send O
    duration += DASH_DURATION_MILLIS;
    duration += DOT_DURATION_MILLIS;
    duration += DASH_DURATION_MILLIS;
    duration += DOT_DURATION_MILLIS; 
    duration += DASH_DURATION_MILLIS;
    duration += 3 * DOT_DURATION_MILLIS;

    // send E
    duration += DOT_DURATION_MILLIS;
    duration += 7 * DOT_DURATION_MILLIS;

    return duration;
}
