#include "sandbox.h"

//Xylophone
//Adapted for an ArduinoMega
//from Jenna deBoisblanc and Spiekenzie Labs initial code

//*******************************************************************************************************************
// User settable variables
//*******************************************************************************************************************

uint8_t TOM_LOW = 41;
uint8_t TOM_MID = 43;
uint8_t TOM_LHIGH = 45;
uint8_t SNARE_ROCK = 40;
uint8_t HH_CLOSED = 42;
uint8_t RIDE_ROCK = 50;

int pinRead;
uint8_t pinAssignments[16] = { A0, A1, A2, A3, A4, A5 };
byte PadNote[16] = { TOM_LOW, TOM_MID, TOM_LHIGH, SNARE_ROCK, HH_CLOSED, RIDE_ROCK };  // MIDI notes from 0 to 127 (Mid C = 60)
int PadCutOff[16] = { 70, 70, 70, 70, 70, 70 };  // Minimum Analog value to cause a drum hit
int MaxPlayTime[16] = { 100, 100, 100, 100, 100, 100 };  // Cycles before a 2nd hit is allowed
#define  midichannel 1;                              // MIDI channel from 0 to 15 (+1 in "real world")
boolean VelocityFlag = false;                           // Velocity ON (true) or OFF (false)

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
  pinMode(A0, INPUT);
}
//*******************************************************************************************************************
// Main Program
//*******************************************************************************************************************
void loop() {
  //delay(1000);
  //Serial.println("Test");

//  for (uint8_t index = 0; index < 16; index++) {
//    MIDI_NOTE_ON(PadNote[index], 127);
//    delay(500);
//  }

  for (pin = 0; pin < 6; pin++) {
    hitavg = analogRead(pinAssignments[pin]);
//  if(hitavg > 500){
//    MIDI_NOTE_ON(PadNote[pin], hitavg);
//    delay(1000);
//  }
    //Serial.println(hitavg);
    // read the input pin

    if ((hitavg > PadCutOff[pin])) {
      if ((activePad[pin] == false)) {
        if (VelocityFlag == true) {
          //          hitavg = 127 / ((1023 - PadCutOff[pin]) / (hitavg - PadCutOff[pin]));    // With full range (Too sensitive ?)
          hitavg = (hitavg / 8) - 1;                                                 // Upper range
        } else {
          hitavg = 127;
        }
        MIDI_NOTE_ON(PadNote[pin], hitavg);  //note on

        PinPlayTime[pin] = 0;
        activePad[pin] = true;
      } else {
        PinPlayTime[pin] = PinPlayTime[pin] + 1;
      }
    } else if ((activePad[pin] == true)) {
      PinPlayTime[pin] = PinPlayTime[pin] + 1;
      if (PinPlayTime[pin] > MaxPlayTime[pin]) {
        activePad[pin] = false;
        //MIDI_NOTE_ON(PadNote[pin], 0);
      }
    }
  }
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

void MIDI_NOTE_ON(byte PITCH, byte VELOCITY) {
  MIDI_TX(144, PITCH, VELOCITY);
}

void MIDI_NOTE_OFF(byte PITCH, byte VELOCITY) {
  MIDI_TX(128, PITCH, VELOCITY);
}
