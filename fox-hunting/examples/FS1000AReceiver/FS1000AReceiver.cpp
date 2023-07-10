#include "RH_ASK.h"
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver(1200);

const uint8_t BUZZER_PIN = 3;
uint32_t lastBeepMillis = 0;
uint8_t buzzerState = 0;
#define RSSI_NUMBER_OF_SAMPLES 32
uint16_t rssi[RSSI_NUMBER_OF_SAMPLES];

uint16_t calculateAverageRssi(uint16_t currentRssi);
uint16_t averageRssi;

void setup()
{
    // Receiver pin must be connected to Arduino pin D11
    Serial.begin(115200);	// Debugging only
    if (driver.init())
    {
        Serial.println("[RH_ASK] init succeeded");
        Serial.print(F("[RH_ASK] speed is "));
        Serial.print(driver.speed());
        Serial.println(F(" bps"));
    }
    else
    {
        Serial.println("[RH_ASK] init failed");
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

             Serial.println(averageRssi); 
        }

        uint16_t lastRSSI = driver.lastRssi();
        averageRssi = calculateAverageRssi(lastRSSI);
    }

    if((lastBeepMillis + 60 < millis()) && buzzerState == 1)
    {
        analogWrite(BUZZER_PIN, 0);
        buzzerState = 0;
    }
}

uint16_t calculateAverageRssi(uint16_t currentRssi)
{
    uint16_t summ = 0;
    for(uint8_t index = 0 ; index < RSSI_NUMBER_OF_SAMPLES - 1; index ++)
    {
        rssi[index] = rssi[index + 1];
        summ += rssi[index];
    }

    rssi[RSSI_NUMBER_OF_SAMPLES - 1] = currentRssi;
    summ += currentRssi;

    // divide by 32
    return summ >> 5;
}
