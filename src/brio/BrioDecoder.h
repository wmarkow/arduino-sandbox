/*
 * BrioDecoder.h
 *
 *  Created on: 08.05.2018
 *      Author: wmarkowski
 */

#ifndef BRIO_BRIODECODER_H_
#define BRIO_BRIODECODER_H_

#include <Array.h>
#include "BrioMessage.h"
#include "../ir/IRData.h"

class BrioDecoder
{
public:
   bool decode(Array<IRData>* receivedData, BrioMessage* result);
   void encode(BrioMessage* result, Array<IRData>* rawData);

private:
   uint8_t decodeBit(uint16_t toggleDuration, uint16_t spaceDuration);
   uint8_t decodeChannel(Array<IRData>* receivedData);
   uint8_t decodeCommand(Array<IRData>* receivedData);
   void encodeBit(bool bit, Array<IRData>* rawData);
   void encodeChannel(uint8_t channel, Array<IRData>* rawData);
   void encodeCommand(uint8_t command, Array<IRData>* rawData);
};

#endif /* BRIO_BRIODECODER_H_ */
