/*
 * WebRadioCLient.cpp
 *
 *  Created on: 28.09.2018
 *      Author: wmarkowski
 */

#include "WebRadioClient.h"

const char* host = "ice3.somafm.com";
int httpPort = 80;
const char* path = "/u80s-64-aac";

#define BUFFER_SIZE 32
uint8_t buffer[BUFFER_SIZE];

String millisToHMS(unsigned long millis);

WebRadioClient::WebRadioClient() :
      player(VS1053(VS1053_CS, VS1053_DCS, VS1053_DREQ))
{

}

bool WebRadioClient::begin(const char* ssid, const char *passphrase)
{
   WiFi.begin(ssid, passphrase);
   WiFi.setAutoConnect(true);
   WiFi.setAutoReconnect(true);

   player.begin();
   player.switchToMp3Mode();
   player.setVolume(VOLUME);

   return player.isChipConnected();
}

void WebRadioClient::loop()
{
   wl_status_t wifiStatus = WiFi.status();

   if (lastWifiStatus != wifiStatus)
   {
      switch (wifiStatus)
      {
         case WL_NO_SHIELD:
            Serial.println(F("WiFi WL_NO_SHIELD"));
            break;
         case WL_IDLE_STATUS:
            Serial.println(F("WiFi WL_IDLE_STATUS"));
            break;
         case WL_NO_SSID_AVAIL:
            Serial.println(F("WiFi WL_NO_SSID_AVAIL"));
            break;
         case WL_SCAN_COMPLETED:
            Serial.println(F("WiFi WL_SCAN_COMPLETED"));
            break;
         case WL_CONNECTED:
            Serial.println(F("WiFi WL_CONNECTED"));
            Serial.println(WiFi.localIP());
            break;
         case WL_CONNECT_FAILED:
            Serial.println(F("WiFi WL_CONNECT_FAILED"));
            break;
         case WL_CONNECTION_LOST:
            Serial.println(F("WiFi WL_CONNECTION_LOST"));
            break;
         case WL_DISCONNECTED:
            Serial.println(F("WiFi WL_DISCONNECTED"));
            WiFi.reconnect();
            break;
         default:
            Serial.println(F("WiFi UNKNOWN"));
      }
   }

   if (wifiStatus != WL_CONNECTED)
   {
      wifiClient.stop();
      webRadioClientState = CONNECTING;
      lastWifiStatus = wifiStatus;

      return;
   }

   if (lastWifiStatus != WL_CONNECTED && wifiStatus == WL_CONNECTED)
   {
      // connected to WiFi
      webRadioClientState = CONNECTING;
   }

   lastWifiStatus = wifiStatus;

   switch (webRadioClientState)
   {
      case CONNECTING:
      {
         if (player.isChipConnected() == true)
         {
            Serial.println("VS1053 connected.");
         }
         else
         {
            Serial.println("VS1053 not connected!");
         }

         if (!wifiClient.connect(host, httpPort))
         {
            Serial.println("Connection failed");
            return;
         }
         else
         {
            wifiClient.print(
                  String("GET ") + path + " HTTP/1.1\r\n" + "Host: " + host
                        + "\r\n" + "Connection: close\r\n\r\n");

            Serial.println("Connected to WebRadio");
            webRadioClientState = CONNECTED;
         }
         break;
      }
      case CONNECTED:
      {
         if (!wifiClient.connected())
         {
            wifiClient.stop();
            webRadioClientState = CONNECTING;

            return;
         }

         if (wifiClient.available() >= BUFFER_SIZE)
         {
            uint8_t bytesread = wifiClient.read(buffer, BUFFER_SIZE);
            player.playChunk(buffer, bytesread);
         }

         do1secTasks();
         break;
      }
      default:
         wifiClient.stop();
         webRadioClientState = CONNECTING;
         break;
   }
}

bool WebRadioClient::reinitVS1053()
{
   Serial.println("VS1053 reinit!");

   player.begin();
   player.switchToMp3Mode();
   // a trick to force VS1053 library to reset the volume
   uint8_t volume = player.getVolume();
   player.setVolume(volume + 1);
   player.setVolume(volume - 1);
   player.setVolume(volume);

   bool result = player.isChipConnected();
   if (result)
   {
      Serial.println("VS1053 reinit OK.");
   }
   else
   {
      Serial.println("VS1053 reinit fail!");
   }

   return result;
}

void WebRadioClient::do1secTasks()
{
   if (millis() - last1secTasksMillis > 1000)
   {
      last1secTasksMillis = millis();

      bool currentIsChipConnected = player.isChipConnected();
      if (currentIsChipConnected == false)
      {
         Serial.println("VS1053 not connected!");
      }
      if (previousIsChipConnected == false && currentIsChipConnected == true)
      {
         // chip reconnected
         reinitVS1053();
      }
      previousIsChipConnected = currentIsChipConnected;
   }
}
