#include "sandbox.h"

#include <LCDKeypadShield.h>
#include <LCDKeypadShield_I2C.h>
#include <Terminal.h>
#include <Array.h>
#include <FixedSizeArray.h>
#include <AbstractCommand.h>
#include <UptimeCommand.h>

LCDKeypadShield_I2C lcd(0x3F,16,2);

FixedSizeArray<AbstractCommand*, 5> commands;
Array<AbstractCommand*> *cmd = &commands;
UptimeCommand uptimeCommand;

Terminal terminal(&Serial, cmd);

void setup() {
	Serial.begin(9600);

	lcd.init();
	lcd.backlight();

	// Print a message to the LCD.
	lcd.print(F("Hello world!"));

	commands.add(&uptimeCommand);
}

void loop() {
	terminal.loop();
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
