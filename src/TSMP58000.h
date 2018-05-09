/*
 * TSMP58000.h
 *
 *  Created on: 25.04.2018
 *      Author: wmarkowski
 */

#ifndef TSMP58000_H_
#define TSMP58000_H_

#include <Array.h>
#include "ir/IRData.h"

class TSMP58000
{
public:
   bool read(Array<IRData>* array);
   void dump(Array<IRData>* array);
private:
   uint32_t toggleDurationInMicros;
   uint16_t toggleCount;
};

#endif /* TSMP58000_H_ */
