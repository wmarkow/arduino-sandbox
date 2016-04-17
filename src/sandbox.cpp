#include "sandbox.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
	Serial.println(F("Hello world!"));

	delay(1000);
}
