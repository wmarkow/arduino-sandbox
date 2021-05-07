
#ifndef SRC_DISTILLERDATA_H_
#define SRC_DISTILLERDATA_H_

#include <stdint.h>

const float DISTILLER_INVALID_TEMP = -273.0;

class DistillerData
{
public:
    unsigned long systemUpTime;
    float coldWaterTemp = DISTILLER_INVALID_TEMP;
    float hotWaterTemp = DISTILLER_INVALID_TEMP;
    float waterRpm = 0;
    float headerTemp = DISTILLER_INVALID_TEMP;
    float kegTemp = DISTILLER_INVALID_TEMP;

    uint8_t* getArray();
    uint8_t getArraySize();
};



#endif /* SRC_DISTILLERDATA_H_ */
