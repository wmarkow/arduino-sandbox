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
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "MonostableSwitch.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void onDoorBellSwitchPressed();
void onDoorBellSwitchReleased();

MonostableSwitch doorSwitch(2);

// the setup function runs once when you press reset or power the board
void setup() {
	mySoftwareSerial.begin(9600);
	  Serial.begin(9600);

	  Serial.println();
	  Serial.println(F("DFRobot DFPlayer Mini Demo"));
	  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

	  doorSwitch.setOnSwitchOn(&onDoorBellSwitchPressed);
	  doorSwitch.setOnSwitchOff(&onDoorBellSwitchReleased);

	  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
	    Serial.println(F("Unable to begin:"));
	    Serial.println(F("1.Please recheck the connection!"));
	    Serial.println(F("2.Please insert the SD card!"));
	    while(true);
	  }
	  Serial.println(F("DFPlayer Mini online."));

	  myDFPlayer.volume(15);  //Set volume value. From 0 to 30
	  //myDFPlayer.playMp3Folder(1);  //Play the first mp3
}

// the loop function runs over and over again forever
void loop() {
	doorSwitch.loop();

//	static unsigned long timer = millis();

//	  if (millis() - timer > 5000) {
//	    timer = millis();
//	    myDFPlayer.next();  //Play next mp3 every 3 second.
//	  }
//
//	  if (myDFPlayer.available()) {
//	    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
//	  }                      // wait for a second


}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void onDoorBellSwitchPressed()
{
	Serial.println(F("Door bell switch pressed."));
	myDFPlayer.playMp3Folder(11);
}

void onDoorBellSwitchReleased()
{
	Serial.println(F("Door bell switch released."));
	myDFPlayer.playMp3Folder(12);
}
