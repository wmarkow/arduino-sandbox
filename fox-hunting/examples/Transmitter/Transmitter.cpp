#include <Arduino.h>
#include <HC12.h>

HC12 hc12;

void setup()
{
    Serial.begin(115200);

    hc12.begin();
}

void loop()
{
    for(uint8_t q = 0 ; q < 5 ; q ++)
    {
        hc12.write(255);
        delay(100);
    }
   
    delay(500);
}