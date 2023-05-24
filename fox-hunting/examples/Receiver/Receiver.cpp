#include <Arduino.h>
#include <HC12.h>

HC12 hc12;
const uint8_t BUZZER_PIN = 3;
uint32_t lastBeepMillis = 0;

void setup()
{
    Serial.begin(115200);

    hc12.begin();

    pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    uint8_t byte = 0;
    while(hc12.available() > 0)
    {
        // read one byte
        if(hc12.read(&byte, 1) == 1)
        {
            if(byte == 255)
            {
                // read what has been sent
                Serial.println("Received byte");
                tone(BUZZER_PIN, 1000);
                lastBeepMillis = millis();
            }
        }
    }

    if(lastBeepMillis + 200 < millis())
    {
        noTone(BUZZER_PIN);
    }

}