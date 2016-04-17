#include "sandbox.h"

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int read_LCD_buttons();

void setup() {
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(F("Hello, world!"));
}

void loop() {
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(9, 1);
	// print the number of seconds since reset:
	lcd.print(millis() / 1000);


	 lcd.setCursor(0,1);            // move to the begining of the second line
	 lcd_key = read_LCD_buttons();  // read the buttons

	switch (lcd_key)               // depending on which button was pushed, we perform an action
	{
		case btnRIGHT:
		{
			lcd.print("RIGHT ");
			break;
		}
		case btnLEFT:
		{
			lcd.print("LEFT   ");
			break;
		}
		case btnUP:
		{
			lcd.print("UP    ");
			break;
		}
		case btnDOWN:
		{
			lcd.print("DOWN  ");
	    	break;
		}
		case btnSELECT:
		{
			lcd.print("SELECT");
			break;
		}
		case btnNONE:
		{
			lcd.print("NONE  ");
			break;
		}
	}
}

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);

 if (adc_key_in > 1000) return btnNONE;
 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 250)  return btnUP;
 if (adc_key_in < 450)  return btnDOWN;
 if (adc_key_in < 650)  return btnLEFT;
 if (adc_key_in < 850)  return btnSELECT;

 return btnNONE;
}
