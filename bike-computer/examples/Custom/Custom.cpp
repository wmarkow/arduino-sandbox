/*
 * main.cpp
 *
 *  Created on: 26 wrz 2019
 *      Author: wmarkow
 */

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Array.h>
#include <com/github/wmarkow/bike/dashboards/custom/CustomDashboard.h>
#include <com/github/wmarkow/bike/dashboards/custom/CustomDashCommand.h>
#include <FixedSizeArray.h>
#include <HardwareSerial.h>
#include <PinChangeInterrupt.h>
#include <Print.h>
#include <stdint.h>
#include <Terminal.h>
#include <Wire.h>
#include <WString.h>

#define WHEEL_SENSOR_PIN 2

CustomDashboard customDashboard;

FixedSizeArray<AbstractCommand*, 5> commands;
Array<AbstractCommand*> *commandsArray = &commands;
Terminal terminal(&Serial, commandsArray);
CustomDashCommand dashCommand(&customDashboard);

void onSpeedSensorEvent();
void scanI2C();

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
void testdrawline();
void testdrawchar(void);

void setup()
{
   Serial.begin(9600);
   commandsArray->add(&dashCommand);

   customDashboard.init();

   pinMode(WHEEL_SENSOR_PIN, INPUT_PULLUP);
   attachPCINT(digitalPinToPCINT(WHEEL_SENSOR_PIN), onSpeedSensorEvent,
   FALLING);

   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
   { // Address 0x3C for 128x32
      Serial.println(F("SSD1306 allocation failed"));
   }
   // Show initial display buffer contents on the screen --
   // the library initializes this with an Adafruit splash screen.
   display.display();
   delay(2000); // Pause for 2 seconds

   // Clear the buffer
   display.clearDisplay();

   // Draw a single pixel in white
   display.drawPixel(10, 10, SSD1306_WHITE);

   // Show the display buffer on the screen. You MUST call display() after
   // drawing commands to make them visible on screen!
   display.display();
   delay(2000);
   // display.display() is NOT necessary after every single drawing command,
   // unless that's what you want...rather, you can batch up a bunch of
   // drawing operations and then update the screen all at once by calling
   // display.display(). These examples demonstrate both approaches...

   testdrawline();      // Draw many lines
   testdrawchar();      // Draw characters of the default font

   // Invert and restore display, pausing in-between
   display.invertDisplay(true);
   delay(1000);
   display.invertDisplay(false);
   delay(1000);
}

void loop(void)
{
   terminal.loop();
   customDashboard.loop();
}

void onSpeedSensorEvent()
{
   customDashboard.tickSpeedSensor(millis());

//   uint8_t speed = speedSensor.getSpeed();
//   float acceleration = speedSensor.getAcceleration();
//
//   Serial.print(speed);
//   Serial.print("   ");
//   Serial.println(acceleration);
}

void scanI2C()
{
   byte error, address;
   int nDevices;

   Serial.println("Scanning...");

   nDevices = 0;
   for (address = 1; address < 127; address++)
   {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0)
      {
         Serial.print("I2C device found at address 0x");
         if (address < 16)
         {
            Serial.print("0");
         }
         Serial.print(address, HEX);
         Serial.println("  !");

         nDevices++;
      }
      else if (error == 4)
      {
         Serial.print("Unknown error at address 0x");
         if (address < 16)
         {
            Serial.print("0");
         }
         Serial.println(address, HEX);
      }
   }
   if (nDevices == 0)
   {
      Serial.println("No I2C devices found\n");
   }
   else
   {
      Serial.println("done\n");
   }
}

void testdrawline()
{
   int16_t i;

   display.clearDisplay(); // Clear display buffer

   for (i = 0; i < display.width(); i += 4)
   {
      display.drawLine(0, 0, i, display.height() - 1, SSD1306_WHITE);
      display.display(); // Update screen with each newly-drawn line
      delay(1);
   }
   for (i = 0; i < display.height(); i += 4)
   {
      display.drawLine(0, 0, display.width() - 1, i, SSD1306_WHITE);
      display.display();
      delay(1);
   }
   delay(250);

   display.clearDisplay();

   for (i = 0; i < display.width(); i += 4)
   {
      display.drawLine(0, display.height() - 1, i, 0, SSD1306_WHITE);
      display.display();
      delay(1);
   }
   for (i = display.height() - 1; i >= 0; i -= 4)
   {
      display.drawLine(0, display.height() - 1, display.width() - 1, i,
      SSD1306_WHITE);
      display.display();
      delay(1);
   }
   delay(250);

   display.clearDisplay();

   for (i = display.width() - 1; i >= 0; i -= 4)
   {
      display.drawLine(display.width() - 1, display.height() - 1, i, 0,
      SSD1306_WHITE);
      display.display();
      delay(1);
   }
   for (i = display.height() - 1; i >= 0; i -= 4)
   {
      display.drawLine(display.width() - 1, display.height() - 1, 0, i,
      SSD1306_WHITE);
      display.display();
      delay(1);
   }
   delay(250);

   display.clearDisplay();

   for (i = 0; i < display.height(); i += 4)
   {
      display.drawLine(display.width() - 1, 0, 0, i, SSD1306_WHITE);
      display.display();
      delay(1);
   }
   for (i = 0; i < display.width(); i += 4)
   {
      display.drawLine(display.width() - 1, 0, i, display.height() - 1,
      SSD1306_WHITE);
      display.display();
      delay(1);
   }

   delay(2000); // Pause for 2 seconds
}

void testdrawchar(void)
{
   display.clearDisplay();

   display.setTextSize(1);      // Normal 1:1 pixel scale
   display.setTextColor(SSD1306_WHITE); // Draw white text
   display.setCursor(0, 0);     // Start at top-left corner
   display.cp437(true);         // Use full 256 char 'Code Page 437' font

   // Not all the characters will fit on the display. This is normal.
   // Library will draw what it can and the rest will be clipped.
   for (int16_t i = 0; i < 256; i++)
   {
      if (i == '\n')
         display.write(' ');
      else
         display.write(i);
   }

   display.display();
   delay(2000);
}
