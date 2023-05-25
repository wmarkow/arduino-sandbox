#include <Arduino.h>
#include <HC12.h>

HC12 hc12;
const uint8_t BUZZER_PIN = 3;
uint32_t lastBeepMillis = 0;

uint8_t buzzerState = 0; 

void setup()
{
    Serial.begin(115200);

    hc12.begin();

    pinMode(BUZZER_PIN, OUTPUT);
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
            if(byte == 255)
            {
                // read what has been sent
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
            tone(BUZZER_PIN, 1000);
        }
    }

    if((lastBeepMillis + 100 < millis()) && buzzerState == 1)
    {
        Serial.print(millis());
        Serial.println(" OFF");
        noTone(BUZZER_PIN);
        buzzerState = 0;
    }

}