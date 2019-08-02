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

#define JOYSTICK_X_INPUT A0
#define JOYSTICK_Y_INPUT A1
#define TURBO_BUTTON_INPUT 2

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
Joystick joystick(JOYSTICK_X_INPUT, JOYSTICK_Y_INPUT);

void setup()
{
    pinMode(TURBO_BUTTON_INPUT, INPUT);

    Serial.begin(9600);

    lastDisplayTime = 0;
    joystick.setReverseY(true);
    joystick.setZeroValueThreshold(20);

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
        int16_t joystickX = joystick.readX();
        int16_t joystickY = joystick.readY();
        uint8_t turboButton = digitalRead(TURBO_BUTTON_INPUT);

        if (!turboButton)
        {
            joystickY >>= 1;
        }

        // create a datagram and send it to the receiver
        RCDatagram rcDatagrm;
        int8_t speedInPercent = map(joystickY, -512, 512, -100, 100);
        rcDatagrm.speedInPercent = speedInPercent;
        // TODO: send this as UDP
        //radioRF24.sendTcp(DST_ADDRESS, (uint8_t*) &rcDatagrm, sizeof(RCDatagram));

        if (joystickX != 0 || speedInPercent != 0)
        {
            char tbs[50];
            sprintf(tbs, "X=%03d Y=%03d T=%1d", joystickX, speedInPercent,
                    turboButton);
            Serial.println(tbs);
        }

        lastDisplayTime = millis();
    }
}
