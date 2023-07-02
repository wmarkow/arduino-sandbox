#include "RH_ASK.h"
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

const uint8_t BUZZER_PIN = 3;
uint32_t lastBeepMillis = 0;
uint8_t buzzerState = 0;

void setup()
{
    // Receiver pin must be connected to Arduino pin D11
    Serial.begin(115200);	// Debugging only
    if (driver.init())
    {
        Serial.println("init succeeded");
    }
    else
    {
        Serial.println("init failed");
    }   
}

void loop()
{
    uint8_t newBuzzerState = buzzerState;

    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
        newBuzzerState = 1;
        lastBeepMillis = millis();  

        if(buzzerState == 0 && newBuzzerState == 1)
        {
            buzzerState = 1;
            analogWrite(BUZZER_PIN, 127);
        }    
    }

    if((lastBeepMillis + 60 < millis()) && buzzerState == 1)
    {
        analogWrite(BUZZER_PIN, 0);
        buzzerState = 0;
    }
}
