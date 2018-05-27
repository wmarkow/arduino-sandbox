/*
 * BrioDecoder.cpp
 *
 *  Created on: 08.05.2018
 *      Author: wmarkowski
 */

#include "BrioMessage.h"
#include "BrioDecoder.h"
#include "../ir/IRData.h"

#define      PULSE_LONG 1500 // in micros
#define     PULSE_SHORT 500  // in micros

#define  PULSE_LONG_MIN PULSE_LONG - 100
#define  PULSE_LONG_MAX PULSE_LONG + 100
#define PULSE_SHORT_MIN PULSE_SHORT - 100
#define PULSE_SHORT_MAX PULSE_SHORT + 100

#define PRETOGGLE 6000
#define PRETOGGLE_MIN PRETOGGLE - 100
#define PRETOGGLE_MAX PRETOGGLE + 100

bool BrioDecoder::decode(Array<IRData>* receivedData, BrioMessage* result)
{
   if (receivedData->getSize() != 18)
   {
      return false;
   }

   for (uint8_t q = 0; q < receivedData->getSize(); q++)
   {
      IRData* ptr = receivedData->peek(q);
      if (q % 2 == 0 && ptr->type != IR_TYPE_TOGGLE)
      {
         // it is not IR Toggle, rise error
         return false;
      }
      if (q % 2 == 1 && ptr->type != IR_TYPE_SPACE_HIGH)
      {
         // it is not IR Space High, rise error
         return false;
      }
   }

   if (receivedData->peek(0)->duration > PRETOGGLE_MIN
         && receivedData->peek(0)->duration < PRETOGGLE_MAX
         && receivedData->peek(1)->duration > PULSE_SHORT_MIN
         && receivedData->peek(1)->duration < PULSE_SHORT_MAX)
   {
      // ok
   }
   else
   {
      return false;
   }

   uint8_t channel = decodeChannel(receivedData);
   if (channel != BRIO_CHANNEL_A && channel != BRIO_CHANNEL_B)
   {
      return false;
   }

   uint8_t command = decodeCommand(receivedData);
   result->channel = channel;
   result->command = command;

   return true;
}

void BrioDecoder::encode(BrioMessage* message, Array<IRData>* rawData)
{
   rawData->clear();

   //generate pretoggle
   IRData irData;
   irData.type = IR_TYPE_TOGGLE;
   irData.duration = PRETOGGLE;
   rawData->add(&irData);

   irData.type = IR_TYPE_SPACE_HIGH;
   irData.duration = PULSE_SHORT;
   rawData->add(&irData);

   encodeChannel(message->channel, rawData);
   encodeCommand(message->command, rawData);
}

/***
 * Toggle Long
 * Space Short
 * will be considered as bit 1
 * Other combinations are considered as bit 0.
 */
uint8_t BrioDecoder::decodeBit(uint16_t toggleDuration, uint16_t spaceDuration)
{
   if (toggleDuration > PULSE_LONG_MIN && toggleDuration < PULSE_LONG_MAX
         && spaceDuration > PULSE_SHORT_MIN)
   {
      return 1;
   }

   return 0;
}


uint8_t BrioDecoder::decodeChannel(Array<IRData>* receivedData)
{
   uint8_t channel = 0;

   for (uint8_t q = 0; q < 4; q++)
   {
      uint8_t index = 2 + 2 * q;
      channel <<= 1;
      channel |= decodeBit(receivedData->peek(index)->duration,
            receivedData->peek(index + 1)->duration);
   }

   return channel;
}

uint8_t BrioDecoder::decodeCommand(Array<IRData>* receivedData)
{
   uint8_t command = 0;

   for (uint8_t q = 0; q < 4; q++)
   {
      uint8_t index = 10 + 2 * q;
      command <<= 1;
      command |= decodeBit(receivedData->peek(index)->duration,
            receivedData->peek(index + 1)->duration);
   }

   return command;
}

void BrioDecoder::encodeBit(bool bit, Array<IRData>* rawData)
{
   IRData irData;
   if (bit)
   {
      irData.duration = PULSE_LONG;
      irData.type = IR_TYPE_TOGGLE;
      rawData->add(&irData);

      irData.duration = PULSE_SHORT;
      irData.type = IR_TYPE_SPACE_HIGH;
      rawData->add(&irData);
   }
   else
   {
      irData.duration = PULSE_SHORT;
      irData.type = IR_TYPE_TOGGLE;
      rawData->add(&irData);

      irData.duration = PULSE_LONG;
      irData.type = IR_TYPE_SPACE_HIGH;
      rawData->add(&irData);
   }
}

void BrioDecoder::encodeChannel(uint8_t channel, Array<IRData>* rawData)
{
   for (int8_t q = 3; q >= 0; q--)
   {
      bool bit = channel & (1 << q);
      encodeBit(bit, rawData);
   }
}

void BrioDecoder::encodeCommand(uint8_t command, Array<IRData>* rawData)
{
   for (int8_t q = 3; q >= 0; q--)
   {
      bool bit = command & (1 << q);
      encodeBit(bit, rawData);
   }
}
