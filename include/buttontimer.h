#ifndef BUTTONTIMER_H
#define BUTTONTIMER_H

#include "buttoneventhandler.h"
#include <SmingCore.h>

class ButtonTimer {
public:
  ButtonTimer(ButtonEventHandler &buttonEventHandler);
  virtual ~ButtonTimer();

private:
  Timer timer;
  int pressCounter;
  void tick();
  ButtonEventHandler &buttonEventHandler;
};

#endif // BUTTONTIMER_H
