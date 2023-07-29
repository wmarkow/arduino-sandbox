#include "RH_ASK.h"
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver(1200);

const uint8_t BUZZER_PIN = 3;
uint32_t lastBeepMillis = 0;
uint32_t lastRssiPrintMillis = 0;
uint8_t buzzerState = 0;
uint16_t rssi[32];
uint16_t rspi[32];

uint16_t calculateAverageRssi(uint16_t currentRssi);
uint16_t calculateAverageRspi(uint16_t currentRspi);
uint16_t averageRssi;
uint16_t averageRspi;

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

        uint16_t lastRSPI = driver.lastRspi();
        averageRspi = calculateAverageRspi(lastRSPI);
        
        if(buzzerState == 0 && newBuzzerState == 1)
        {
            buzzerState = 1;
            // RSPI = 0 map to 1000 Hz
            // RSPI = 100 map to 3000 Hz
            if(averageRspi > 1023)
            {
                averageRspi = 1023;
            }
            unsigned int freq = map(averageRspi, 0, 1023, 1000, 3000);
            tone(BUZZER_PIN, freq);

            //Serial.println(averageRspi); 
        }
    }

    if((lastBeepMillis + 60 < millis()) && buzzerState == 1)
    {
        noTone(BUZZER_PIN);
        buzzerState = 0;
    }

    if(millis() - lastRssiPrintMillis > 100)
    {
        Serial.println(driver.lastRssi());
        lastRssiPrintMillis = millis();
    }
}

uint16_t calculateAverageRssi(uint16_t currentRssi)
{
    uint16_t summ = 0;
    for(uint8_t index = 0 ; index < 32 - 1; index ++)
    {
        rssi[index] = rssi[index + 1];
        summ += rssi[index];
    }

    rssi[32 - 1] = currentRssi;
    summ += currentRssi;

    // divide by 32
    return summ >> 5;
}

uint16_t calculateAverageRspi(uint16_t currentRspi)
{
    uint16_t summ = 0;
    for(uint8_t index = 0 ; index < 32 - 1; index ++)
    {
        rspi[index] = rspi[index + 1];
        summ += rspi[index];
    }

    rspi[32 - 1] = currentRspi;
    summ += currentRspi;

    // divide by 32
    return summ >> 5;
}
