/*
 * SerialRadio.h
 *
 *  Created on: 24.11.2017
 *      Author: wmarkowski
 */

#ifndef SERIALRADIO_H_
#define SERIALRADIO_H_

#include <radio.h>
#include <RDSParser.h>

void RDS_process(uint16_t block1, uint16_t block2, uint16_t block3,
      uint16_t block4);
void DisplayServiceName(char *name);
void DisplayText(char *name);
void DisplayTime(uint8_t hour, uint8_t minute);

/// State definition for this radio implementation.
enum RADIO_STATE
{
   STATE_PARSECOMMAND, ///< waiting for a new command character.

   STATE_PARSEINT,     ///< waiting for digits for the parameter.
   STATE_EXEC          ///< executing the command.
};

class SerialRadio
{

public:
   SerialRadio(RADIO* radio);
   void init();
   void loop();

private:
   RADIO* radio;
   RADIO_STATE state; ///< The state variable is used for parsing input characters.

   void runSerialCommand(char cmd, int16_t value);
};

#endif /* SERIALRADIO_H_ */
