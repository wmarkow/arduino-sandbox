#include <Arduino.h>
#include "WebRadioClient.h"

const char* ssid = "AndroidAP";
const char* password = "rumcajsa";

WebRadioClient webRadioClient;

void setup()
{
   // initialize digital pin LED_BUILTIN as an output.
   pinMode(LED_BUILTIN, OUTPUT);
   Serial.begin(115200);

   // Wait for VS1053 to power up
   // otherwise the system might not start up correctly
   delay(3000);

   SPI.begin();
   webRadioClient.begin(ssid, password);
}

void loop()
{
   webRadioClient.loop();
}
