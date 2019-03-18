#ifndef TELEGRAPHKEYDECODERLISTENER_H_
#define TELEGRAPHKEYDECODERLISTENER_H_

class TelegraphKeyDecoderListener
{
public:
   virtual void onCharDecoded(char c) = 0;
   virtual void onError() = 0;
};



#endif /* TELEGRAPHKEYDECODERLISTENER_H_ */
