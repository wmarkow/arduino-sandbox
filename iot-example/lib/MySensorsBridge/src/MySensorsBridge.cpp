#include "MySensorsBridge.h"

bool transportInit(void)
{
    return false;
}

void transportSetAddress(const uint8_t address)
{

}

uint8_t transportGetAddress(void)
{
    return 0;
}

bool transportDataAvailable(void)
{
    return false;
}

bool transportSanityCheck(void)
{
    return false;
}

uint8_t transportReceive(void *data)
{
    return 0;
}

bool transportSend(const uint8_t to, const void *data, const uint8_t len, const bool noACK)
{
    return false;
}

void transportPowerDown(void)
{

}

void transportPowerUp(void)
{

}

void transportSleep(void)
{

}

void transportStandBy(void)
{

}

int16_t transportGetSendingRSSI(void)
{
    return INVALID_RSSI;
}

int16_t transportGetReceivingRSSI(void)
{
    return INVALID_RSSI;
}

int16_t transportGetSendingSNR(void)
{
    return INVALID_SNR; 
}

int16_t transportGetReceivingSNR(void)
{
    return INVALID_SNR;
}

int16_t transportGetTxPowerPercent(void)
{
    return 0;
}

bool transportSetTxPowerPercent(const uint8_t powerPercent)
{
    return false;
}

int16_t transportGetTxPowerLevel(void)
{
    return -99;
}