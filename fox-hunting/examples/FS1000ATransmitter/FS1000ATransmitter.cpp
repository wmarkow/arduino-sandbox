#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

const uint16_t DOT_DURATION_MILLIS = 150;
const uint16_t DASH_DURATION_MILLIS = 3 * DOT_DURATION_MILLIS;

RH_ASK driver(4800);

void sendDot();
void sendDash();

void setup()
{
    // Transmitter pin must be connected to Arduino pin D12
    Serial.begin(115200);	  // Debugging only
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
        const char *msg = "H";
        driver.send((uint8_t *)msg, strlen(msg));
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
        const char *msg = "H";
        driver.send((uint8_t *)msg, strlen(msg));
    }

    Serial.print(millis());
    Serial.println(" DASH end");
}