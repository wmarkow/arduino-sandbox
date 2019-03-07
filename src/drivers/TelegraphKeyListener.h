#ifndef DRIVERS_TELEGRAPHKEYLISTENER_H_
#define DRIVERS_TELEGRAPHKEYLISTENER_H_

class TelegraphKeyListener
{
public:
   virtual void onTelegraphKeyPressed() = 0;
   virtual void onTelegraphKeyReleased() = 0;
};



#endif /* DRIVERS_TELEGRAPHKEYLISTENER_H_ */
