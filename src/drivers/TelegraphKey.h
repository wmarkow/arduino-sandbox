#ifndef DRIVERS_TELEGRAPHKEY_H_
#define DRIVERS_TELEGRAPHKEY_H_

#include "AbstractSwitch.h"

class TelegraphKey : public AbstractSwitch
{
private:
   void (*onKeyPressedCallback)();
   void (*onKeyReleasedCallback)();

protected:
   void onSwitchOnInternal();
   void onSwitchOffInternal();

public:
   TelegraphKey(uint8_t pin);
   void setOnKeyPressedCallback(void (*callback)());
   void setOnKeyReleasedCallback(void (*callback)());
};

#endif /* DRIVERS_TELEGRAPHKEY_H_ */
