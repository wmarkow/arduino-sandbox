#include "MySensorsBridge.h"
#include <mesh/network/node/MeshNode.h>
#include <mesh/link/HC12Device.h>

MeshNode localMeshNode;
HC12Device hc12Device;
Interface radioInterface = Interface(&hc12Device);


bool transportInit(void)
{
    Serial.println(F("BRIDGE:TRAN:INIT"));

    localMeshNode.setInterface(0, &radioInterface);
    radioInterface.getDevice()->up();

	return radioInterface.getDevice()->isChipConnected();
}

void transportSetAddress(const uint8_t address)
{
    Serial.println(F("BRIDGE:TRAN:SETADDRESS"));

    localMeshNode.setIpAddress(address);
}

uint8_t transportGetAddress(void)
{
    Serial.println(F("BRIDGE:TRAN:GETADDRESS"));

    return localMeshNode.getIpAddress();
}

bool transportDataAvailable(void)
{
    Serial.println(F("BRIDGE:TRAN:DATAAVAILABLE"));

    return false;
}

bool transportSanityCheck(void)
{
    Serial.println(F("BRIDGE:TRAN:SANITYCHECK"));

    return false;
}

uint8_t transportReceive(void *data)
{
    Serial.println(F("BRIDGE:TRAN:RECEIVE"));

    return 0;
}

bool transportSend(const uint8_t to, const void *data, const uint8_t len, const bool noACK)
{
    Serial.println(F("BRIDGE:TRAN:SEND"));

    if(noACK)
    {
        // UDP packet
    }
    else
    {
        // TCP packet
    }
    return false;
}

void transportPowerDown(void)
{
    Serial.println(F("BRIDGE:TRAN:POWERDOWN"));
}

void transportPowerUp(void)
{
    Serial.println(F("BRIDGE:TRAN:POWERUP"));
}

void transportSleep(void)
{
    Serial.println(F("BRIDGE:TRAN:SLEEP"));
}

void transportStandBy(void)
{
    Serial.println(F("BRIDGE:TRAN:STANDBY"));
}

int16_t transportGetSendingRSSI(void)
{
    Serial.println(F("BRIDGE:TRAN:GETSENDINGRSSI"));

    return INVALID_RSSI;
}

int16_t transportGetReceivingRSSI(void)
{
    Serial.println(F("BRIDGE:TRAN:GETRECEIVINGRSSI"));

    return INVALID_RSSI;
}

int16_t transportGetSendingSNR(void)
{
    Serial.println(F("BRIDGE:TRAN:GETSENDINGSNR"));

    return INVALID_SNR; 
}

int16_t transportGetReceivingSNR(void)
{
    Serial.println(F("BRIDGE:TRAN:GETRECEIVINGSNR"));

    return INVALID_SNR;
}

int16_t transportGetTxPowerPercent(void)
{
    Serial.println(F("BRIDGE:TRAN:GETTXPOWERPERCENT"));

    return 0;
}

bool transportSetTxPowerPercent(const uint8_t powerPercent)
{
    Serial.println(F("BRIDGE:TRAN:SETTXPOWERPERCENT"));

    return false;
}

int16_t transportGetTxPowerLevel(void)
{
    Serial.println(F("BRIDGE:TRAN:GETTXPOWERLEVEL"));

    return -99;
}