/*
 * CustomDashboard.cpp
 *
 *  Created on: 9 maj 2020
 *      Author: wmarkowski
 */

#include <Arduino.h>
#include "CustomDashboard.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS 0x3C

CustomDashboard::CustomDashboard() :
      display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire)
{

}

void CustomDashboard::init()
{
   speedGauge.init();
   speedGauge.setValueRange(0, 60);
   speedGauge.reset();

   speedSensor.setWheelDiameter(24);
   speedSensorEnabled = true;

   if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS))
   {
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

   display.clearDisplay();
   display.setTextSize(2);
   display.setCursor(0, 0);
   display.write("Licznik");
   display.setCursor(16, 16);
   display.write("Kuby");
   display.display();
}

void CustomDashboard::loop()
{
   speedGauge.loop();

   if (speedSensorEnabled == true)
   {
      uint8_t speed = speedSensor.getSpeed();
      speedGauge.setValue(speed);
   }
}

void CustomDashboard::reset()
{
   speedGauge.reset();
}

void CustomDashboard::tickSpeedSensor(unsigned long millis)
{
   speedSensor.tick(millis);
}

void CustomDashboard::setSpeed(uint8_t speed)
{
   speedSensorEnabled = false;
   speedGauge.setValue(speed);
}

void CustomDashboard::testdrawline()
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

void CustomDashboard::testdrawchar(void)
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

