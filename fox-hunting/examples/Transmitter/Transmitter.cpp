#include <Arduino.h>
#include <HC12.h>

const uint16_t DOT_DURATION_MILLIS = 150;
const uint16_t DASH_DURATION_MILLIS = 3 * DOT_DURATION_MILLIS;

HC12 hc12;
char text[100];

void sendDot();
void sendDash();

void setup()
{
    Serial.begin(115200);

    hc12.begin();

   //hc12.switchSerialPortTo2400bps();

    if(hc12.setTxPowerValue(1) == 0)
    {
        Serial.println("Setting Tx power to -1dBm");
    }
    else
    {
        Serial.println("Setting Tx power failed");
    }

    uint16_t dataRate =  hc12.getAirDataRateInKbs();
    sprintf(text, "dataRate = %d kbps", dataRate);
    Serial.println(text);
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
    while(millis() < startTime + DASH_DURATION_MILLIS)
    {
        hc12.write(255);
        delay(25);
    }

    Serial.print(millis());
    Serial.println(" DASH end");
}