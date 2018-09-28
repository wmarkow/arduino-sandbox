#include "Arduino.h"
#include "WebRadioClient.h"

const char* ssid = "AndroidAP";
const char* password = "rumcajsa";

WebRadioClient webRadioClient;

void setup()
{
   // initialize digital pin LED_BUILTIN as an output.
   pinMode(LED_BUILTIN, OUTPUT);
   Serial.begin(9600);
   webRadioClient.begin(ssid, password);
}

void loop()
{
   webRadioClient.loop();
}
