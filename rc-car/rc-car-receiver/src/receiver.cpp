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

#include "RCDatagram.h"

#define IP_ADDRESS 2

RF24Device rf24Device;
Interface radioRF24 = Interface(&rf24Device);

// dummy start
HC12Device hc12Device;
Interface radioHC12 = Interface(&hc12Device);
// dummy end

FixedSizeArray<AbstractCommand*, 4> commands;
Array<AbstractCommand*> *commandsArray = &commands;
UptimeCommand uptimeCommand;
Ping pingCommand;
Ifconfig ifconfigCommand;
IpConfig ipConfigCommand;
Terminal terminal(&Serial, commandsArray);

void setup()
{
    Serial.begin(9600);

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
    radioRF24.loop();
}
