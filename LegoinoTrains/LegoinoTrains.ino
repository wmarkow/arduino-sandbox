/**
 * A Legoino example to emulate a train hub which directly sends
 * out the motor commands as IR signals to a power function IR receiver. 
 * With this setup you can upgrade your power function systems to powerup systems
 * 
 * For the setup the IR LED has to be connected on the OUTPUT PIN 12 of the 
 * ESP controller. This will work out of the Box with the M5 Atom matrix/light
 * esp32 board which has a build in IR LED on Port 12
 * 
 * Port A of the powered up hub is mapped to the RED power function port
 * Port B of the powered up hub is mapped to the BLUE power function port
 * 
 * Example video: https://www.youtube.com/watch?v=RTNexxT4-yQ&t=16s
 * 
 * (c) Copyright 2020 - Cornelius Munz
 * Released under MIT License
 * 
 */

#include <Arduino.h>
#include <analogWrite.h>
#include "Lpf2HubEmulation.h"
#include "PowerFunctions.h"
#include "LegoinoCommon.h"

// create a hub instance
Lpf2HubEmulation myEmulatedHub("Hub", HubType::POWERED_UP_HUB);

// create a power functions instance (IR LED on Pin 12, IR Channel 0)
// PowerFunctions pf(12, 0);

#define MOTOR_A_PWM 14 // Motor A PWM Speed connect to IA of L9110
#define MOTOR_A_DIR 12 // Motor A Direction connect to IB of L9110

void writeValueCallback(byte port, byte value)
{
  Serial.println("writeValueCallback: ");
  Serial.println(port, HEX);
  Serial.println(value, HEX);

  if (port == 0x00)
  {
    // pf.single_pwm(PowerFunctionsPort::RED, pf.speedToPwm(value));
    Serial.print("Hub Port A speed command received. "); 

    if(value == 0x00 || value == 0x7F)
    {
       // stop
       digitalWrite( MOTOR_A_DIR, LOW );
       analogWrite( MOTOR_A_PWM, 0 );

       return;
    }
    if(value < 0x7F)
    {
       // forward
       digitalWrite( MOTOR_A_DIR, LOW ); // direction = forward
       // the more duty cycle the faster speed
       int pwm = map(value, 0, 127, 0, 255);
       analogWrite( MOTOR_A_PWM, pwm ); // PWM speed = fast

       return;
    }

    if(value > 0x7F)
    {
       // reverse
       digitalWrite( MOTOR_A_DIR, HIGH ); // direction = reverse
       // the low duty cycle the faster speed
       analogWrite( MOTOR_A_PWM, 0 ); // PWM speed = fast

       return;
    }
  }

  if (port == 0x01)
  {
    //pf.single_pwm(PowerFunctionsPort::BLUE, pf.speedToPwm(value));
    Serial.print("Hub Port B speed command received. ");
  }

  if (port == 0x32)
  {
    Serial.print("Hub LED command received with color: ");
    Serial.println(LegoinoCommon::ColorStringFromColor(value).c_str());
  }
}

void setup()
{
  pinMode( MOTOR_A_DIR, OUTPUT );
  pinMode( MOTOR_A_PWM, OUTPUT );
  digitalWrite( MOTOR_A_DIR, LOW );
  digitalWrite( MOTOR_A_PWM, LOW );
  
  Serial.begin(115200);
  // define the callback function if a write message event on the characteristic occurs
  myEmulatedHub.setWritePortCallback(&writeValueCallback); 
  myEmulatedHub.start();
}

// main loop
void loop()
{
  //Serial.println("loop...");
  // if an app is connected, attach some devices on the ports to signalize 
  // the app that values could be received/written to that ports
  if (myEmulatedHub.isConnected && !myEmulatedHub.isPortInitialized)
  {
    delay(1000);
    myEmulatedHub.isPortInitialized = true;
    myEmulatedHub.attachDevice((byte)PoweredUpHubPort::A, DeviceType::TRAIN_MOTOR);
    delay(1000);
    myEmulatedHub.attachDevice((byte)PoweredUpHubPort::LED, DeviceType::HUB_LED);
    delay(1000);
    myEmulatedHub.attachDevice((byte)PoweredUpHubPort::B, DeviceType::TRAIN_MOTOR);
    delay(1000);
  }

} // End of loop
