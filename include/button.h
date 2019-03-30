#ifndef BUTTON_H
#define BUTTON_H
#include <SmingCore.h>
#include <functional>
#include <initializer_list>

namespace Button {
enum class State { pressingSince, pressedFor, releasingSince, releasedFor };

struct Event {
  const State state;
  const int from;
  const int to;
  const std::function<void(int)> action;

  Event(State state, int from, int to, std::function<void(int)> action)
      : state(state), from(from), to(to), action(action) {}
};

namespace {
static void processButtonHandler(State state, int ms, const Event *event) {
  if ((state == event->state) && (event->from <= ms) && (ms <= event->to))
    event->action(ms);
}
} // namespace

template <uint16_t pin, uint32_t intervalMs, const struct Event *... T>
class ButtonTimer {
private:
  int counter;
  State state;
  Timer timer;

  void tick() {
    bool buttonState = !static_cast<bool>(digitalRead(pin));
    switch (state) {
    case State::pressingSince:
      if (buttonState)
        ++counter;
      else
        state = State::pressedFor;
      break;
    case State::pressedFor:
    case State::releasedFor:
      counter = 0;
      if (buttonState)
        state = State::pressingSince;
      else
        state = State::releasingSince;
      break;
    case State::releasingSince:
      if (buttonState)
        state = State::releasedFor;
      else
        ++counter;
      break;
    }
    std::initializer_list<int>{
        (processButtonHandler(state, counter * intervalMs, T), 0)...};
  }

public:
  ButtonTimer() {
    pinMode(pin, INPUT);
    state = State::releasingSince;
    counter = 0;
    timer
        .initializeMs(
            intervalMs,
            TimerDelegate(&ButtonTimer<pin, intervalMs, T...>::tick, this))
        .start();
  }

  virtual ~ButtonTimer() { timer.stop(); }
};

} // namespace Button
#endif // BUTTON_H
