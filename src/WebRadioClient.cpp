/*
 * WebRadioCLient.cpp
 *
 *  Created on: 28.09.2018
 *      Author: wmarkowski
 */

#include "WebRadioClient.h"

const char* host = "comet.shoutca.st";
int httpPort = 8563;
const char* path = "/1";

#define BUFFER_SIZE 32
uint8_t buffer[BUFFER_SIZE];
unsigned long lastPrintTime = 0;
unsigned long readBytes = 0;

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

   return isChipConnected();
}

bool WebRadioClient::isChipConnected()
{
   return player.testComm("Test");
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
            Serial.println(F("WiFi WL_NWL_CONNECTEDO_SHIELD"));
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
         if (isChipConnected() == false)
         {
            Serial.println("VS1053 not connected!");
         }
         else
         {
            Serial.println("VS1053 connected.");
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
            lastAvailableStreamMillis = millis();
         }
         break;
      }
      case CONNECTED:
      {
         if (millis() - lastAvailableStreamMillis > 5000)
         {
            // timeout
            wifiClient.stop();
            webRadioClientState = CONNECTING;
            return;
         }

         if (wifiClient.available())
         {
            if (wifiClient.available() >= BUFFER_SIZE)
            {
               uint8_t bytesread = wifiClient.read(buffer, BUFFER_SIZE);
               player.playChunk(buffer, bytesread);
               readBytes += BUFFER_SIZE;

               // send the buffer to external device
               lastAvailableStreamMillis = millis();
            }
         }

         if (millis() - lastPrintTime > 1000)
         {
            lastPrintTime = millis();
            String hms = millisToHMS(lastPrintTime);

            Serial.print(hms);
            Serial.print(F(" "));
            Serial.println(readBytes);
         }
         break;
      }
      default:
         wifiClient.stop();
         webRadioClientState = CONNECTING;
         break;
   }
}

// macros from DateTime.h
/* Useful Constants */
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)

/* Useful Macros for getting elapsed time */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)

String millisToHMS(unsigned long millis)
{
   unsigned long time = millis / 1000;
   uint8_t hours = numberOfHours(time);
   uint8_t minutes = numberOfMinutes(time);
   uint8_t seconds = numberOfSeconds(time);
   uint16_t secondFraction = millis % 1000;

   String result;
   if (hours < 10)
   {
      result += "0";
   }
   result += hours;
   result += ":";
   if (minutes < 10)
   {
      result += "0";
   }
   result += minutes;
   result += ":";
   if (seconds < 10)
   {
      result += "0";
   }
   result += seconds;
   result += ".";
   if (secondFraction < 10)
   {
      result += "00";
   }
   else if (secondFraction < 100)
   {
      result += "0";
   }
   result += secondFraction;

   return result;
}
