#include "sandbox.h"

#include "LCDKeypadShield.h"

LCDKeypadShield lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(F("Witaj!"));
}

void loop() {
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(9, 1);
	// print the number of seconds since reset:
	lcd.print(millis() / 1000);

	lcd.setCursor(0,1);

	switch (lcd.getButton())
	{
		case BUTTON_RIGHT:
		{
			lcd.print("PRAWO ");
			break;
		}
		case BUTTON_LEFT:
		{
			lcd.print("LEWO  ");
			break;
		}
		case BUTTON_UP:
		{
			lcd.print("GORA  ");
			break;
		}
		case BUTTON_DOWN:
		{
			lcd.print("DOL   ");
	    	break;
		}
		case BUTTON_SELECT:
		{
			lcd.print("SELECT");
			break;
		}
		case BUTTON_NONE:
		{
			lcd.print("NIC   ");
			break;
		}
	}
}
