#ifndef LOCALTELEGRAPH_H_
#define LOCALTELEGRAPH_H_

#include <Arduino.h>
#include "drivers/TelegraphKey.h"
#include "drivers/TelegraphKeyListener.h"

class LocalTelegraph : public TelegraphKeyListener
{
public:
   LocalTelegraph();
   void init();
   void loop();

private:
   TelegraphKey telegraphKey;
   void onTelegraphKeyPressed();
   void onTelegraphKeyReleased();
};

#endif /* LOCALTELEGRAPH_H_ */
