#ifndef BUTTONEVENTHANDLER_H
#define BUTTONEVENTHANDLER_H

class ButtonEventHandler {
public:
  virtual ~ButtonEventHandler() {}

  virtual void pressingSince(int ms) = 0;
  virtual void pressedFor(int ms) = 0;

  virtual void releasingSince(int ms) = 0;
  virtual void releasedFor(int ms) = 0;
};
#endif // BUTTONEVENTHANDLER_H
