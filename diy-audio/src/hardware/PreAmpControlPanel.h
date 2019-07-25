/*
 * PreAmpControlPanel.h
 *
 *  Created on: 29.12.2017
 *      Author: wmarkowski
 */

#ifndef HARDWARE_PREAMPCONTROLPANEL_H_
#define HARDWARE_PREAMPCONTROLPANEL_H_

#include "PreAmp.h"

class PreAmpControlPanel
{
private:
   PreAmp *preAmp;
   void checkVolumePot();
   void checkInputChannelPot();
public:
   PreAmpControlPanel(PreAmp *preAmp);
   PreAmp* getPreAmp();
   void loop();
};

#endif /* HARDWARE_PREAMPCONTROLPANEL_H_ */
