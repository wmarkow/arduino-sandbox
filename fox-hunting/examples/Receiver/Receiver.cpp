#include <Arduino.h>
#include <HC12.h>

HC12 hc12;
const uint8_t BUZZER_PIN = 3;
uint32_t lastBeepMillis = 0;

uint8_t buzzerState = 0; 

char text[100];

unsigned int countSetBits(unsigned int n);

void setup()
{
    Serial.begin(115200);

    hc12.begin();

    pinMode(BUZZER_PIN, OUTPUT);

    //hc12.switchSerialPortTo2400bps();

    uint16_t dataRate =  hc12.getAirDataRateInKbs();
    sprintf(text, "dataRate = %d kbps", dataRate);
    Serial.println(text);
}

void loop()
{
    uint8_t byte = 0;
    uint8_t newBuzzerState = buzzerState;
    while(hc12.available() > 0)
    {
        // read one byte
        if(hc12.read(&byte, 1) == 1)
        {
            // Transmitter sends one byte with the value of 255.
            // Allow for some bit error rate during transmission.
            if(countSetBits(byte) > 4)
            {
                // The fact: accepting some bit rate error doesn't help much to extend
                // the range of the transmission. HC-12 uses Si4463 under the hood
                // to transmitt the data and the data are organised there already
                // in packets. In case of transmisison errors the packet is flushed
                // (probably because of CRC mismatch).
                // In other words: HC-12 receives only correctly received packets, so
                // basically we receive always what the transmitter has sent. In case
                // of transmission errors we receive nothing.
                Serial.print(millis());
                Serial.println(" REBY");
                newBuzzerState = 1;
                lastBeepMillis = millis();
            }
        }

        if(buzzerState == 0 && newBuzzerState == 1)
        {
            Serial.print(millis());
            Serial.println(" BUZZ");
            buzzerState = 1;
            analogWrite(BUZZER_PIN, 127);
        }
    }

    if((lastBeepMillis + 60 < millis()) && buzzerState == 1)
    {
        Serial.print(millis());
        Serial.println(" OFF");
        analogWrite(BUZZER_PIN, 0);
        buzzerState = 0;
    }

}

unsigned int countSetBits(unsigned int n)
{
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}