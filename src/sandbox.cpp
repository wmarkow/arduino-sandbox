#include "sandbox.h"

//Xylophone
//Adapted for an ArduinoMega
//from Jenna deBoisblanc and Spiekenzie Labs initial code

//*******************************************************************************************************************
// User settable variables
//*******************************************************************************************************************

int pinRead;
char pinAssignments[16] = { 'A0', 'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7', 'A8', 'A9', 'A10', 'A11' };
byte PadNote[16] = { 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };  // MIDI notes from 0 to 127 (Mid C = 60)
int PadCutOff[16] = { 400, 400, 200, 800, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400 };  // Minimum Analog value to cause a drum hit
int MaxPlayTime[16] = { 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90 };  // Cycles before a 2nd hit is allowed
#define  midichannel 1;                              // MIDI channel from 0 to 15 (+1 in "real world")
boolean VelocityFlag = true;                           // Velocity ON (true) or OFF (false)

//*******************************************************************************************************************
// Internal Use Variables
//*******************************************************************************************************************
boolean activePad[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };   // Array of flags of pad currently playing
int PinPlayTime[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };           // Counter since pad started to play
byte status1;

int pin = 0;
int hitavg = 0;
//*******************************************************************************************************************
// Setup
//*******************************************************************************************************************
void setup() {
  Serial.begin(9600);                                  // SET HAIRLESS TO THE SAME BAUD RATE IN THE SETTINGS

}
//*******************************************************************************************************************
// Main Program
//*******************************************************************************************************************
void loop() {
  delay(1000);
  //Serial.println("Test");

  for (uint8_t index = 0; index < 16; index++) {
    MIDI_TX(144, PadNote[index], 127);
    delay(500);
  }

  //MIDI_TX(128, PadNote[0], 0);
//  for (int pin = 0; pin < 16; pin++)                          //
//      {
//    //int pin = 3;
//    //   for (pinRead=0; pinRead < 16, pin++){
//    hitavg = analogRead(pinAssignments[pin]);
//    //Serial.println(hitavg);
//    // read the input pin
//
//    if ((hitavg > PadCutOff[pin])) {
//      if ((activePad[pin] == false)) {
//        if (VelocityFlag == true) {
//          //          hitavg = 127 / ((1023 - PadCutOff[pin]) / (hitavg - PadCutOff[pin]));    // With full range (Too sensitive ?)
//          hitavg = (hitavg / 8) - 1;                                                 // Upper range
//        } else {
//          hitavg = 127;
//        }
//        MIDI_TX(144, PadNote[pin], hitavg);  //note on
//
//        PinPlayTime[pin] = 0;
//        activePad[pin] = true;
//      } else {
//        PinPlayTime[pin] = PinPlayTime[pin] + 1;
//      }
//    } else if ((activePad[pin] == true)) {
//      PinPlayTime[pin] = PinPlayTime[pin] + 1;
//      if (PinPlayTime[pin] > MaxPlayTime[pin]) {
//        activePad[pin] = false;
//        MIDI_TX(144, PadNote[pin], 0);
//      }
//    }
//  }
}

//*******************************************************************************************************************
// Transmit MIDI Message
//*******************************************************************************************************************
void MIDI_TX(byte MESSAGE, byte PITCH, byte VELOCITY) {
  status1 = MESSAGE + (uint8_t) midichannel
  ;

  Serial.write(status1);
  Serial.write(PITCH);
  Serial.write(VELOCITY);

}
