#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

void setup()
{
    // Transmitter pin must be connected to Arduino pin D12
    Serial.begin(115200);	  // Debugging only
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
    Serial.print("sending packet... ");
    const char *msg = "Hello World!";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println("done.");
    delay(1000);
}
