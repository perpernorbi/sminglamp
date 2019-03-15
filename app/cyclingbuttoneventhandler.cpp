#include "cyclingbuttoneventhandler.h"

CyclingButtonEventHandler::CyclingButtonEventHandler(
    CyclingStateMachineInterface &cycler)
    : cycler(cycler) {}

void CyclingButtonEventHandler::pressingSince(int ms) {
  if (1000 == ms)
    cycler.reset();
}

void CyclingButtonEventHandler::pressedFor(int ms) {
  if (ms < 500)
    cycler.next();
}

void CyclingButtonEventHandler::releasingSince(int ms){};
void CyclingButtonEventHandler::releasedFor(int ms){};
