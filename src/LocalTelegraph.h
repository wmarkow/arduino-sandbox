#ifndef LOCALTELEGRAPH_H_
#define LOCALTELEGRAPH_H_

#include <Arduino.h>
#include "drivers/TelegraphKey.h"

void onTelegraphKeyPressed();
void onTelegraphKeyReleased();

class LocalTelegraph
{
public:
   LocalTelegraph();
   void init();
   void loop();

private:
   TelegraphKey telegraphKey;
};

#endif /* LOCALTELEGRAPH_H_ */
