#include "debugbuttoneventhandler.h"
#include <SmingCore.h>

void DebugButtonEventHandler::pressingSince(int ms) {
  debugf("pressingSince %dms", ms);
}

void DebugButtonEventHandler::pressedFor(int ms) {
  debugf("pressedFor %dms", ms);
}

void DebugButtonEventHandler::releasingSince(int ms) {
  debugf("releasingSince %dms", ms);
}

void DebugButtonEventHandler::releasedFor(int ms) {
  debugf("releasedFor %dms", ms);
}
