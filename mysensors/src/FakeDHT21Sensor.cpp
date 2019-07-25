/*
 * FakeTemperatureSensor.cpp
 *
 *  Created on: 21.06.2018
 *      Author: wmarkowski
 */

#include "FakeDHT21Sensor.h"

FakeDHT21Sensor::FakeDHT21Sensor(NodeManager& node_manager, int child_id) :
      Sensor(node_manager)
{
   _name = "FaKE SHT21";
   children.allocateBlocks(2);
   new ChildFloat(this, _node->getAvailableChildId(child_id), S_TEMP, V_TEMP,
         _name);
   new ChildFloat(this, _node->getAvailableChildId(child_id + 1), S_HUM, V_HUM,
         _name);
}

// what to do during setup
void FakeDHT21Sensor::onSetup()
{
}

// what to do during loop
void FakeDHT21Sensor::onLoop(Child* child)
{
   if (child->getType() == V_TEMP)
   {
      // read the temperature
      float temperature = 21;
      // convert it
      temperature = _node->celsiusToFahrenheit(temperature);
      // store the value
      ((ChildFloat*) child)->setValueFloat(temperature);
   }
   else if (child->getType() == V_HUM)
   {
      // read humidity
      float humidity = 50;
      // store the value
      ((ChildFloat*) child)->setValueFloat(humidity);
   }
}

void FakeDHT21Sensor::onReceive(MyMessage* message) {
  Child* child = getChild(message->sensor);
  if (child == nullptr) return;
  if (message->getCommand() == C_REQ && message->type == child->getType()) onLoop(child);
}

