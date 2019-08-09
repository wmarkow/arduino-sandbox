#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdint.h>
#include <WString.h>

#include <L298N.h>

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

FixedSizeArray<AbstractCommand*, 4> commands;
Array<AbstractCommand*> *commandsArray = &commands;
UptimeCommand uptimeCommand;
Ping pingCommand;
Ifconfig ifconfigCommand;
IpConfig ipConfigCommand;
Terminal terminal(&Serial, commandsArray);

#define MAIN_MOTOR_PWM_PIN 6
#define MAIN_MOTOR_IN1_PIN 7
#define MAIN_MOTOR_IN2_PIN 8

#define MAIN_WHEEL_PWM_PIN 3
#define MAIN_WHEEL_IN1_PIN 2
#define MAIN_WHEEL_IN2_PIN 4

L298N mainMotor(MAIN_MOTOR_PWM_PIN, MAIN_MOTOR_IN1_PIN, MAIN_MOTOR_IN2_PIN);
L298N steeringWheel(MAIN_WHEEL_PWM_PIN, MAIN_WHEEL_IN1_PIN, MAIN_WHEEL_IN2_PIN);

unsigned long lastReceivedDatagramMillis = 0;

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

    mainMotor.setSpeed(0);
    mainMotor.stop();

    steeringWheel.setSpeed(0);
    steeringWheel.stop();
}

void setSpeed(int8_t speed, uint8_t turboButtonState);
void setSteering(int8_t steering);

void loop(void)
{
    terminal.loop();
    LocalMeshNode.loop();

    IotPacket* incomingPacket = LocalMeshNode.getIncomingPacket();
    if (incomingPacket != NULL)
    {
        RCDatagram* rcDatagram = (RCDatagram*) incomingPacket->payload;
        int8_t speed = rcDatagram->speedInPercent;
        int8_t steering = rcDatagram->steeringAngleInPercent;
        uint8_t turboButtonState = rcDatagram->turboButtonState;

        LocalMeshNode.markIncomingPacketConsumed();

        char tbs[50];
        sprintf(tbs, "V=%03d S=%03d T=%1d", speed, steering, turboButtonState);
        Serial.println(tbs);

        setSpeed(speed, turboButtonState);
        setSteering(steering);

        lastReceivedDatagramMillis = millis();
    }

    if (millis() - lastReceivedDatagramMillis > 500)
    {
        // no communication since 500ms
        setSpeed(0, 0);
        setSteering(0);
    }
}

void setSpeed(int8_t speed, uint8_t turboButtonState)
{
    if (turboButtonState == 0)
    {
        speed = 0.5 * speed;
    }

    if (speed == 0)
    {
        mainMotor.setSpeed(0);
        mainMotor.stop();
    }
    else if (speed > 0)
    {
        uint8_t newSpeed = map(abs(speed), 0, 100, 0, 255);
        mainMotor.setSpeed(newSpeed);
        mainMotor.forward();
    }
    else if (speed < 0)
    {
        uint8_t newSpeed = map(abs(speed), 0, 100, 0, 255);
        mainMotor.setSpeed(newSpeed);
        mainMotor.backward();
    }
}

void setSteering(int8_t steering)
{
    if (steering > -50 && steering < 50)
    {
        steeringWheel.setSpeed(0);
        steeringWheel.stop();
    }
    else if (steering >= 50)
    {
        steeringWheel.setSpeed(255);
        steeringWheel.forward();
    }
    else if (steering <= 50)
    {
        steeringWheel.setSpeed(255);
        steeringWheel.backward();
    }
}
