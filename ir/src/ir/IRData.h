/*
 * IRData.h
 *
 *  Created on: 08.05.2018
 *      Author: wmarkowski
 */

#ifndef IR_IRDATA_H_
#define IR_IRDATA_H_

enum IRType
{
   IR_TYPE_TOGGLE, IR_TYPE_SPACE_LOW, IR_TYPE_SPACE_HIGH
};

struct IRData
{
   IRType type;
   uint16_t duration;
};

#endif /* IR_IRDATA_H_ */
