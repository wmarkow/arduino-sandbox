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

private:
   uint8_t decodeBit(uint16_t toggleDuration, uint16_t spaceDuration);
   uint8_t decodeChannel(Array<IRData>* receivedData);
   uint8_t decodeCommand(Array<IRData>* receivedData);
};

#endif /* BRIO_BRIODECODER_H_ */
