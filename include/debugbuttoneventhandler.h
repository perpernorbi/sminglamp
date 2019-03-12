#ifndef DEBUGBUTTONEVENTHANDLER_H
#define DEBUGBUTTONEVENTHANDLER_H
#include "buttoneventhandler.h"

class DebugButtonEventHandler : public ButtonEventHandler {
public:
  void pressingSince(int ms) override;
  void pressedFor(int ms) override;

  void releasingSince(int ms) override;
  void releasedFor(int ms) override;
};

#endif // DEBUGBUTTONEVENTHANDLER_H
