
#include "DistillerData.h"

uint8_t* DistillerData::getArray()
{
    return (uint8_t*) (&coldWaterTemp);
}

uint8_t DistillerData::getArraySize()
{
    return 20;
}
