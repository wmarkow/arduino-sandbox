
#include "DistillerData.h"

uint8_t* DistillerData::getArray()
{
    return (uint8_t*) (&systemUpTime);
}

uint8_t DistillerData::getArraySize()
{
    return 24;
}
