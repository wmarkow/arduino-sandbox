#include "TelegraphKey.h"

#include <stddef.h>
#include <stdint.h>

TelegraphKey::TelegraphKey(uint8_t pin) :
      AbstractSwitch(pin)
{
}

void TelegraphKey::setTelegraphKeyListener(TelegraphKeyListener* listener)
{
   this->listener = listener;
}

void TelegraphKey::onSwitchOnInternal()
{
   if (listener == NULL)
   {
      return;
   }

   listener->onTelegraphKeyPressed();
}

void TelegraphKey::onSwitchOffInternal()
{
   if (listener == NULL)
   {
      return;
   }

   listener->onTelegraphKeyReleased();
}
