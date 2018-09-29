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
#include <VS1053.h>

#define VS1053_CS     D1
#define VS1053_DCS    D0
#define VS1053_DREQ   D3
// Default volume
#define VOLUME  80

enum WebRadioClientState
{
   CONNECTING, CONNECTED
};

class WebRadioClient
{
public:
   WebRadioClient();
   void loop();
   bool begin(const char* ssid, const char *passphrase);
   bool isChipConnected();
private:
   WiFiClient wifiClient;
   VS1053 player;
   WebRadioClientState webRadioClientState = CONNECTING;
   uint32_t lastAvailableStreamMillis;
   wl_status_t lastWifiStatus = WL_IDLE_STATUS;
};

#endif /* WEBRADIOCLIENT_H_ */
