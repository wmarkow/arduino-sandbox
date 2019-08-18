#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdint.h>
#include <WString.h>

#include <Array.h>
#include <FixedSizeArray.h>

#include <mesh/link/RF24Device.h>
#include <mesh/link/HC12Device.h>
#include <mesh/network/node/MeshNode.h>
#include <mesh/network/interface/Interface.h>

#include <terminal/commands/FlooderCmd.h>
#include <terminal/commands/Ifconfig.h>
#include <terminal/commands/IpConfig.h>
#include <terminal/commands/Ping.h>
#include <Terminal.h>
#include <UptimeCommand.h>

#include "Joystick.h"
#include "RCDatagram.h"

#define RIGHT_JOYSTICK_X_INPUT A0
#define RIGHT_JOYSTICK_Y_INPUT A1
#define L1_BUTTON_INPUT 2
#define STATUS_LED_PIN 7

#define IP_ADDRESS 1
#define DST_ADDRESS 2

RF24Device rf24Device;
Interface radioRF24 = Interface(&rf24Device);

FixedSizeArray<AbstractCommand*, 4> commands;
Array<AbstractCommand*> *commandsArray = &commands;
UptimeCommand uptimeCommand;
Ping pingCommand;
Ifconfig ifconfigCommand;
IpConfig ipConfigCommand;
Terminal terminal(&Serial, commandsArray);

unsigned long lastDisplayTime;
unsigned long lastLedToggle;
Joystick rightJoystick(RIGHT_JOYSTICK_X_INPUT, RIGHT_JOYSTICK_Y_INPUT);

void setup()
{
    pinMode(L1_BUTTON_INPUT, INPUT);
    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, LOW);

    Serial.begin(9600);

    lastDisplayTime = 0;
    rightJoystick.setReverseY(true);
    rightJoystick.setZeroValueThreshold(20);

    randomSeed(analogRead(0));

    commandsArray->add(&uptimeCommand);
    commandsArray->add(&pingCommand);
    commandsArray->add(&ifconfigCommand);
    commandsArray->add(&ipConfigCommand);

    radioRF24.up();
    LocalMeshNode.setRF24Interface(&radioRF24);
    LocalMeshNode.setIpAddress(IP_ADDRESS);
}

void loop(void)
{
    terminal.loop();
    LocalMeshNode.loop();

    if (millis() - lastDisplayTime > 100)
    {
        int16_t joystickX = rightJoystick.readX();
        int16_t joystickY = rightJoystick.readY();
        uint8_t l1Button = digitalRead(L1_BUTTON_INPUT);

        // create a datagram and send it to the receiver
        RCDatagram rcDatagram;
        rcDatagram.rightXInPercent = map(joystickX, -512, 512, -100, 100);
        rcDatagram.rightYInPercent = map(joystickY, -512, 512, -100, 100);
        rcDatagram.l1Button = l1Button;

        LocalMeshNode.sendUdp(DST_ADDRESS, (uint8_t*) &rcDatagram,
                sizeof(RCDatagram));

        char tbs[50];
        sprintf(tbs, "X=%03d Y=%03d T=%1d", rcDatagram.rightXInPercent,
                rcDatagram.rightYInPercent, l1Button);
        Serial.println(tbs);

        lastDisplayTime = millis();
    }

    if (millis() - lastLedToggle > 500)
    {
        digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));
        lastLedToggle = millis();
    }
}
