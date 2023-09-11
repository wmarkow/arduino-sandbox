#include "RH_ASK.h"
#include <SPI.h> // Not actualy used but needed to compile

// Uncomment the line below to enable dumping RSSI values to the serial port.
// Attention: dumping RSSI values to serial port has influence to the sensitivity of the receiver;
// probably the time spent on sending data to serial port is too big and the receiver loses some frames.
// It has been tested: with debug off the device seems to beep more often in the same place.
#define ENABLE_DUMP_RSSI

RH_ASK driver(2400);

const uint8_t BUZZER_PIN = 3;
uint32_t lastBeepMillis = 0;
uint32_t lastRssiPrintMillis = 0;
uint8_t buzzerState = 0;

// WHen low FPS then bigger size of rssi has negative impact to the directional antenna sensitivity of the receiver,
// because it takes more time to calculate the average RSSI
uint16_t rssi[32];
uint16_t rspi[32];

uint16_t calculateAverageRssi(uint16_t currentRssi);
uint16_t calculateAverageRspi(uint16_t currentRspi);
uint16_t averageRssi;
uint16_t averageRspi;

void setup()
{
    // Receiver pin must be connected to Arduino pin D11
    Serial.begin(230400);	// Debugging only
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
    uint16_t lastRssi = driver.lastRssi();

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
        newBuzzerState = 1;
        lastBeepMillis = millis();  

        uint16_t lastRSPI = driver.lastRspi();
        averageRspi = calculateAverageRspi(lastRSPI);
        
        #ifdef ENABLE_DUMP_RSSI
        Serial.print("r");
        Serial.println(lastRssi);
        #endif

        // RSSI is a number between 0 and 1023, with the following meaning:
        // 0 - 199 transmitter is off but receiver gets some garbage (noise)
        // 200 - 450 transmitter is on and receiver gets the carrier
        //  200 receiver is far away from the transmitter
        //  450 receiver is very close to the transmitter
        // 451 - 1023 never get by the receiver
        averageRssi = calculateAverageRssi(lastRssi);
        //averageRssi = averageRssi * 2;
        //Serial.println(driver.lastRssi());
        //Serial.println(averageRssi);

        if(buzzerState == 0 && newBuzzerState == 1)
        {
            buzzerState = 1;
            // RSSI = <=200 map to 1000 Hz
            // RSSI = >=450 map to 3000 Hz
            if(averageRssi > 450)
            {
                averageRspi = 450;
            }
            if(averageRssi < 200)
            {
                averageRssi = 200;
            }
            unsigned int freq = map(averageRssi, 200, 450, 2000, 4000);
            tone(BUZZER_PIN, freq);
        }
    }
    else
    {
        if(millis() - lastRssiPrintMillis > 100)
        {
            #ifdef ENABLE_DUMP_RSSI
            Serial.print("n");
            Serial.println(lastRssi);
            #endif
            lastRssiPrintMillis = millis();
        }
    }

    if((lastBeepMillis + 120 < millis()) && buzzerState == 1)
    {
        noTone(BUZZER_PIN);
        buzzerState = 0;
    } 
}

uint16_t calculateAverageRssi(uint16_t currentRssi)
{
    uint16_t summ = 0;
    for(uint8_t index = 0 ; index < 32 - 1; index ++)
    {
        rssi[index] = rssi[index + 1];
        summ += rssi[index + 1];
    }

    rssi[32 - 1] = currentRssi;
    summ += currentRssi;

    //Serial.print("summ: ");
    //Serial.print(summ);
    //Serial.print("  ");
    //Serial.print("AVG: ");
    //Serial.println(summ >> 5);
    // divide by 32
    return summ >> 5;
}

uint16_t calculateAverageRspi(uint16_t currentRspi)
{
    uint16_t summ = 0;
    for(uint8_t index = 0 ; index < 32 - 1; index ++)
    {
        rspi[index] = rspi[index + 1];
        summ += rspi[index + 1];
    }

    rspi[32 - 1] = currentRspi;
    summ += currentRspi;

    // divide by 32
    return summ >> 5;
}
