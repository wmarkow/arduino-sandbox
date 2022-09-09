#include <stdint.h>

#ifndef MySensorsBridge_h
#define MySensorsBridge_h

#define INVALID_SNR         ((int16_t)-256)	//!< INVALID_SNR
#define INVALID_RSSI        ((int16_t)-256)	//!< INVALID_RSSI
#define INVALID_PERCENT     ((int16_t)-100)	//!< INVALID_PERCENT
#define INVALID_LEVEL       ((int16_t)-256)	//!< INVALID_LEVEL

bool transportInit(void);
void transportSetAddress(const uint8_t address);
uint8_t transportGetAddress(void);
bool transportDataAvailable(void);
bool transportSanityCheck(void);
uint8_t transportReceive(void *data);
bool transportSend(const uint8_t to, const void *data, const uint8_t len, const bool noACK);
void transportPowerDown(void);
void transportPowerUp(void);
void transportSleep(void);
void transportStandBy(void);
int16_t transportGetSendingRSSI(void);
int16_t transportGetReceivingRSSI(void);
int16_t transportGetSendingSNR(void);
int16_t transportGetReceivingSNR(void);
int16_t transportGetTxPowerPercent(void);
bool transportSetTxPowerPercent(const uint8_t powerPercent);
int16_t transportGetTxPowerLevel(void);

#endif //MySensorsBridge_h