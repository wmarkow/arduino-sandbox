/*
 * Display.h
 *
 *  Created on: 4 cze 2020
 *      Author: wmarkowski
 */

#ifndef COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_DISPLAY_H_
#define COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_DISPLAY_H_

#include <Adafruit_SSD1306.h>

class Display
{
private:
   Adafruit_SSD1306 display;
   float speed = 0;
   float acceleration = 0;
   bool breaksOn = false;
   float tripDistance = 0;

   void testdrawline();
   void testdrawchar();
   void displayShowLogo();
   void displayShowDash();
public:
   Display();
   void init();
   void showLogo();
   void showDash();
   void setSpeed(float speed);
   void setAcceleration(float acceleration);
   void setTripDistance(float distance);
   void setBreaksOn(bool breaksOn);
};

#endif /* COM_GITHUB_WMARKOW_BIKE_DASHBOARDS_CUSTOM_DISPLAY_H_ */
