#include "buttontimer.h"
#include <SmingCore.h>

const uint16_t pin = 0;
const uint32_t intervalMs = 100;

ButtonTimer::ButtonTimer(ButtonEventHandler &buttonEventHandler)
    : buttonEventHandler(buttonEventHandler) {
  pinMode(pin, INPUT);
  pressCounter = 0;
  timer.initializeMs(intervalMs, TimerDelegate(&ButtonTimer::tick, this))
      .start();
}

ButtonTimer::~ButtonTimer() { timer.stop(); }

void ButtonTimer::tick() {
  if (digitalRead(pin)) {
    if (pressCounter > 0) {
      buttonEventHandler.pressedFor(pressCounter * intervalMs);
      pressCounter = 0;
    }
    buttonEventHandler.releasingSince(-pressCounter * intervalMs);
    --pressCounter;
  } else {
    if (pressCounter < 0) {
      buttonEventHandler.releasedFor(-pressCounter * intervalMs);
      pressCounter = 0;
    }
    buttonEventHandler.pressingSince(pressCounter * intervalMs);
    ++pressCounter;
  }
};
