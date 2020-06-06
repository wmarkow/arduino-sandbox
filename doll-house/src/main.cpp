#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#include "LightSwitch.h"
#include "PlaySoundSwitch.h"

#define SOUND_OWL_ID 6
#define SOUND_DING_ID 13
#define SOUND_DONG_ID 12

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

PlaySoundSwitch doorSwitch(A0, 0, 24);   // 0 Ohm
PlaySoundSwitch owlSwitch(A0, 124, 137); // 10 kOhm

LightSwitch atticLightSwitch(A5, 6);
LightSwitch bathroomLightSwitch(A1, 2);
LightSwitch bedroomLightSwitch(A4, 5);
LightSwitch livingRoomLightSwitch(A2, 7);

void setup()
{
    doorSwitch.init();
    doorSwitch.setOnSwitchOnSoundId(SOUND_DING_ID);
    doorSwitch.setOnSwitchOffSoundId(SOUND_DONG_ID);

    owlSwitch.init();
    owlSwitch.setOnSwitchOnSoundId(SOUND_OWL_ID);

    atticLightSwitch.init();
    atticLightSwitch.switchOn();

    bathroomLightSwitch.init();
    bathroomLightSwitch.switchOn();

    bedroomLightSwitch.init();
    bedroomLightSwitch.switchOn();

    livingRoomLightSwitch.init();
    livingRoomLightSwitch.switchOn();

    mySoftwareSerial.begin(9600);
    Serial.begin(9600);

    Serial.println();
    Serial.println(F("DFRobot DFPlayer Mini Demo"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    if (!myDFPlayer.begin(mySoftwareSerial))
    {  //Use softwareSerial to communicate with mp3.
        Serial.println(F("Unable to begin:"));
        Serial.println(F("1.Please recheck the connection!"));
        Serial.println(F("2.Please insert the SD card!"));
        while (true)
            ;
    }
    Serial.println(F("DFPlayer Mini online."));

    myDFPlayer.volume(20);  //Set volume value. From 0 to 30
}

void loop()
{
    doorSwitch.loop();
    owlSwitch.loop();

    bathroomLightSwitch.loop();
    bedroomLightSwitch.loop();
    atticLightSwitch.loop();
    livingRoomLightSwitch.loop();
}

void printDetail(uint8_t type, int value)
{
    switch (type)
    {
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
        switch (value)
        {
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
