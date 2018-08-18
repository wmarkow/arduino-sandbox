/*
 Blink

 Turns an LED on for one second, then off for one second, repeatedly.

 Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
 it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
 the correct LED pin independent of which board is used.
 If you want to know what pin the on-board LED is connected to on your Arduino
 model, check the Technical Specs of your board at:
 https://www.arduino.cc/en/Main/Products

 modified 8 May 2014
 by Scott Fitzgerald
 modified 2 Sep 2016
 by Arturo Guadalupi
 modified 8 Sep 2016
 by Colby Newman

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Blink
 */

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "WiFiClient.h"

const char* ssid = "AndroidAP";
const char* password = "rumcajsa";

WiFiClient wifiClient;

const char* host = "ice3.somafm.com";
String url = "/u80s-64-aac";

String millisToHMS(unsigned long millis);

// the setup function runs once when you press reset or power the board
void setup()
{
   // initialize digital pin LED_BUILTIN as an output.
   pinMode(LED_BUILTIN, OUTPUT);
   Serial.begin(9600);
   WiFi.begin(ssid, password);

   // while wifi not connected yet, print '.'
   // then after it connected, get out of the loop
   while (WiFi.status() != WL_CONNECTED)
   {
      delay(500);
      Serial.print(".");
   }
   //print a new line, then print WiFi connected and the IP address
   Serial.println("");
   Serial.println("WiFi connected");
   // Print the IP address
   Serial.println(WiFi.localIP());

   if (!wifiClient.connect(host, 80))
   {
      Serial.println("connection failed");
      return;
   }
   else
   {
      Serial.println("Connected");

//      wifiClient.print("GET /u80s-64-aac");

      wifiClient.print(
            String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n"
                  + "Connection: close\r\n\r\n");

//      ice3.somafm.com/u80s-64-aac
      unsigned long timeout = millis();
      while (wifiClient.available() == 0)
      {
         if (millis() - timeout > 5000)
         {
            Serial.println(">>> Client Timeout !");
            wifiClient.stop();
            return;
         }
      }
   }
}

uint8_t buffer[128];
unsigned long lastPrintTime = 0;
unsigned long readBytes = 0;

// the loop function runs over and over again forever
void loop()
{
   uint8_t chunkSize = 128;

   if (wifiClient.available())
   {
      if (wifiClient.available() >= chunkSize)
      {
         wifiClient.read(buffer, chunkSize);
         readBytes += chunkSize;
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
