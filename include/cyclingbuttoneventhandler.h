#ifndef CYCLINGBUTTONEVENTHANDLER_H
#define CYCLINGBUTTONEVENTHANDLER_H
#include "buttoneventhandler.h"
#include "cyclingStateMachine.h"

class CyclingButtonEventHandler : public ButtonEventHandler {
private:
  CyclingStateMachineInterface &cycler;

public:
  CyclingButtonEventHandler(CyclingStateMachineInterface &cycler);

  virtual void pressingSince(int ms);
  virtual void pressedFor(int ms);

  virtual void releasingSince(int ms);
  virtual void releasedFor(int ms);
};

#endif // CYCLINGBUTTONEVENTHANDLER_H
