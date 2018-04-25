/*
 * TSMP58000.h
 *
 *  Created on: 25.04.2018
 *      Author: wmarkowski
 */

#ifndef TSMP58000_H_
#define TSMP58000_H_

enum IRType
{
   IR_TYPE_TOGGLE,
   IR_TYPE_SILENCE
};

struct IRData
{
   IRType type;
   uint16_t duration;
};

class TSMP58000
{
public:
   bool read();
   uint8_t getReceivedDataSize();
   IRData* getData(uint8_t index);
private:
   IRData receivedData[64];
   int8_t currentIndex;
};

#endif /* TSMP58000_H_ */
