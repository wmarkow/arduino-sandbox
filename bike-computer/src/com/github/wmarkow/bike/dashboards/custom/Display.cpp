/*
 * Display.cpp
 *
 *  Created on: 4 cze 2020
 *      Author: wmarkowski
 */

#include "Display.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS 0x3C

Display::Display() :
      display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire)
{
}

void Display::init()
{
   if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS))
   {
      Serial.println(F("SSD1306 allocation failed"));
   }
   // Normal 1:1 pixel scale
   display.setTextSize(1);
   // Draw white text
   display.setTextColor(SSD1306_WHITE);
   // Start at top-left corner
   display.setCursor(0, 0);
   // Use full 256 char 'Code Page 437' font
   display.cp437(true);

   showLogo();
}

void Display::setSpeed(float speed)
{
   this->speed = speed;
}

void Display::setAcceleration(float acceleration)
{
   this->acceleration = acceleration;
}

void Display::setBreaksOn(bool breaksOn)
{
   this->breaksOn = breaksOn;
}

void Display::testdrawline()
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

void Display::testdrawchar(void)
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

void Display::showLogo()
{
   display.clearDisplay();
   display.setTextSize(2);
   display.setCursor(0, 0);
   display.write("Licznik");
   display.setCursor(16, 16);
   display.write("Kuby");
   display.display();
}

void Display::showDash()
{
   display.clearDisplay();
   display.setTextSize(2); //12x16

   char buffer[10];

   dtostrf(speed, 2, 1, buffer);
   uint8_t length = strlen(buffer);
   display.setCursor(SCREEN_WIDTH - length * 12, 0);
   display.write(buffer);

   dtostrf(acceleration, 4, 1, buffer);
   display.setTextSize(2);
   display.setCursor(0, 0);
   display.write(buffer);

   if(this->breaksOn)
   {
      display.setCursor(SCREEN_WIDTH / 2, 0);
      display.write("H");
   }

   display.display();
}
