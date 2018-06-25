/*
 * FakeSensors.h
 *
 *  Created on: 21.06.2018
 *      Author: wmarkowski
 */

#ifndef SRC_FAKEDHT21SENSOR_H_
#define SRC_FAKEDHT21SENSOR_H_

#include "NodeManagerLibrary.h"

class FakeDHT21Sensor : public Sensor
{
public:
   FakeDHT21Sensor(NodeManager& node_manager, int child_id = -255);
   void onSetup();
   void onLoop(Child* child);
   void onReceive(MyMessage* message);
};

#endif /* SRC_FAKEDHT21SENSOR_H_ */
