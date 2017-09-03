#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "MonostableSwitch.h"
#include "BistableOverMonostableSwitch.h"
#include "LightDriver.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void onDoorBellSwitchPressed();
void onDoorBellSwitchReleased();
void onAtticLightSwitchOn();
void onAtticLightSwitchOff();

MonostableSwitch doorSwitch(A0);
BistableOverMonostableSwitch atticLightSwitch(A5);
LightDriver atticLightDriver(6);

void setup() {
	atticLightDriver.init();
	atticLightDriver.switchOn();
	doorSwitch.init();
	atticLightSwitch.init();

	mySoftwareSerial.begin(9600);
	  Serial.begin(9600);

	  Serial.println();
	  Serial.println(F("DFRobot DFPlayer Mini Demo"));
	  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

	  doorSwitch.setOnSwitchOn(&onDoorBellSwitchPressed);
	  doorSwitch.setOnSwitchOff(&onDoorBellSwitchReleased);
	  atticLightSwitch.setOnSwitchOn(&onAtticLightSwitchOn);
	  atticLightSwitch.setOnSwitchOff(&onAtticLightSwitchOff);

	  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
	    Serial.println(F("Unable to begin:"));
	    Serial.println(F("1.Please recheck the connection!"));
	    Serial.println(F("2.Please insert the SD card!"));
	    while(true);
	  }
	  Serial.println(F("DFPlayer Mini online."));

	  myDFPlayer.volume(15);  //Set volume value. From 0 to 30

	  atticLightDriver.switchOn();
}

void loop() {
	doorSwitch.loop();
	atticLightSwitch.loop();
}

void onDoorBellSwitchPressed()
{
	Serial.println(F("Door bell switch pressed."));
	myDFPlayer.playMp3Folder(13);
}

void onDoorBellSwitchReleased()
{
	Serial.println(F("Door bell switch released."));
	myDFPlayer.playMp3Folder(12);
}

void onAtticLightSwitchOn()
{
	atticLightDriver.switchOn();
}

void onAtticLightSwitchOff()
{
	atticLightDriver.switchOff();
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
