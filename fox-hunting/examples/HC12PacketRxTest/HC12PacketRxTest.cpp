#include <Arduino.h>
#include <HC12.h>

HC12 hc12;
char text[100];
const uint8_t BUZZER_PIN = 3;
uint32_t lastBeepMillis = 0;
uint8_t buzzerState = 0; 

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

    uint16_t dataRate =  hc12.getAirDataRateInKbs();
    sprintf(text, "dataRate = %d kbps", dataRate);
    Serial.println(text);
}

bool calculated = false;
uint16_t recCount = 0;
uint16_t rec1Count = 0;
uint16_t rec2Count = 0;
uint16_t rec4Count = 0;
uint16_t rec8Count = 0;
uint16_t rec16Count = 0;
unsigned long lastReceiveMillis = 0;
uint16_t rssi = 0;

void loop()
{
    uint8_t byte;

    while(hc12.available() > 0)
    {
        // read one byte
        if(hc12.read(&byte, 1) == 1)
        {
            lastReceiveMillis = millis();
            
            if(byte == 1 && calculated == false)
            {
                rssi = (recCount * 100) / 31;
                Serial.print(F("recCount = "));
                Serial.println(recCount);
                Serial.print(F("rssi = "));
                Serial.println(rssi);
                Serial.print(F("rec1Count = "));
                Serial.println(rec1Count);
                Serial.print(F("rec2Count = "));
                Serial.println(rec2Count);
                Serial.print(F("rec4Count = "));
                Serial.println(rec4Count);
                Serial.print(F("rec8Count = "));
                Serial.println(rec8Count);
                Serial.print(F("rec16Count = "));
                Serial.println(rec16Count);

                calculated = true;
                recCount = 0;
                rec1Count = 0;
                rec2Count = 0;
                rec4Count = 0;
                rec8Count = 0;
                rec16Count = 0;

                recCount ++;
                rec1Count ++;
            }
            else
            {
                calculated = false;

                if (byte == 2)
                {
                    recCount ++;
                    rec2Count ++;
                }
                else if (byte == 4)
                {
                    recCount ++;
                    rec4Count ++;
                }
                else if (byte == 8)
                {
                    recCount ++;
                    rec8Count ++;
                }
                else if (byte == 16)
                {
                    recCount ++;
                    rec16Count ++;
                }
                else
                {
                    Serial.println(byte);
                }
            }
        }
    }

    if(millis() > lastReceiveMillis + 500)
    {
        // no reception during 500ms
        rssi = 0;
        Serial.println(0);

        lastReceiveMillis = millis();
    }

    // update buzzer
    //uint16_t beepDurationInMillis = 5000 / rssi;
}
