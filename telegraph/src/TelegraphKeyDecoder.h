#ifndef TELEGRAPHKEYDECODER_H_
#define TELEGRAPHKEYDECODER_H_

#include <Arduino.h>
#include "drivers/TelegraphKey.h"
#include "drivers/TelegraphKeyListener.h"
#include "TelegraphKeyDecoderListener.h"

class TelegraphKeyDecoder : public TelegraphKeyListener
{
public:
   TelegraphKeyDecoder();
   void init();
   void loop();
   void setWpm(uint8_t wpm);
   void setTelegraphKeyDecoderListener(TelegraphKeyDecoderListener *listener);
private:
   uint8_t state;
   TelegraphKey telegraphKey;
   uint32_t lastTimestamp;
   uint16_t dotDuration;
   uint16_t dashDuration;
   byte decodedChar;
   TelegraphKeyDecoderListener *telegraphKeyDecoderListener;
   void onTelegraphKeyPressed();
   void onTelegraphKeyReleased();
};

#endif /* TELEGRAPHKEYDECODER_H_ */
