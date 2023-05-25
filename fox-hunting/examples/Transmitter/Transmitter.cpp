#include <Arduino.h>
#include <HC12.h>

const uint16_t DOT_DURATION_MILLIS = 200;

HC12 hc12;

void sendDot();
void sendDash();

void setup()
{
    Serial.begin(115200);

    hc12.begin();
}

void loop()
{
    // send M
    sendDash();
    delay(DOT_DURATION_MILLIS);  
    sendDash();
    delay(3 * DOT_DURATION_MILLIS);
    
    // send O
    sendDash();
    delay(DOT_DURATION_MILLIS);  
    sendDash();
    delay(DOT_DURATION_MILLIS);  
    sendDash();
    delay(3 * DOT_DURATION_MILLIS);

    // send E
    sendDot();
    delay(7 * DOT_DURATION_MILLIS);
   
    delay(1000);
}

void sendDot()
{
    Serial.print(millis());
    Serial.println(" DOT begin");
    uint32_t startTime = millis();
    while(millis() < startTime + DOT_DURATION_MILLIS)
    {
        hc12.write(255);
        delay(25);
    }

    Serial.print(millis());
    Serial.println(" DOT end");
}

void sendDash()
{
    Serial.print(millis());
    Serial.println(" DASH begin");
    uint32_t startTime = millis();
    while(millis() < startTime + 3 * DOT_DURATION_MILLIS)
    {
        hc12.write(255);
        delay(25);
    }

    Serial.print(millis());
    Serial.println(" DASH end");
}