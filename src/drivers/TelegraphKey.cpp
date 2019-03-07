#include "Arduino.h"
#include "TelegraphKey.h"

TelegraphKey::TelegraphKey(uint8_t pin) :
      AbstractSwitch(pin)
{
   this->onKeyPressedCallback = NULL;
   this->onKeyReleasedCallback = NULL;
}

void TelegraphKey::setOnKeyPressedCallback(void (*callback)())
{
   this->onKeyPressedCallback = callback;
}

void TelegraphKey::setOnKeyReleasedCallback(void (*callback)())
{
   this->onKeyReleasedCallback = callback;
}

void TelegraphKey::onSwitchOnInternal()
{
   if (onKeyPressedCallback == NULL)
   {
      return;
   }

   this->onKeyPressedCallback();
}

void TelegraphKey::onSwitchOffInternal()
{
   if (onKeyReleasedCallback == NULL)
   {
      return;
   }

   this->onKeyReleasedCallback();
}
