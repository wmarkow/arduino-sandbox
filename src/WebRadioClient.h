/*
 * WebRadioClient.h
 *
 *  Created on: 28.09.2018
 *      Author: wmarkowski
 */

#ifndef WEBRADIOCLIENT_H_
#define WEBRADIOCLIENT_H_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

enum WebRadioClientState
{
   CONNECTING, CONNECTED
};

class WebRadioClient
{
public:
   void loop();
   void begin(const char* ssid, const char *passphrase);
private:
   WiFiClient wifiClient;
   WebRadioClientState webRadioClientState = CONNECTING;
   uint32_t lastAvailableStreamMillis;
   wl_status_t lastWifiStatus = WL_IDLE_STATUS;
};

#endif /* WEBRADIOCLIENT_H_ */
