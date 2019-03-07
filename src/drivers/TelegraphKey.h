#ifndef DRIVERS_TELEGRAPHKEY_H_
#define DRIVERS_TELEGRAPHKEY_H_

#include <stddef.h>
#include "AbstractSwitch.h"
#include "TelegraphKeyListener.h"

class TelegraphKey : public AbstractSwitch
{
private:
   TelegraphKeyListener* listener = NULL;

protected:
   void onSwitchOnInternal();
   void onSwitchOffInternal();

public:
   TelegraphKey(uint8_t pin);
   void setTelegraphKeyListener(TelegraphKeyListener* listener);
};

#endif /* DRIVERS_TELEGRAPHKEY_H_ */
