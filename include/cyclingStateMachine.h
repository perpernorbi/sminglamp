#ifndef CYCLINGSTATEMACHINE_H
#define CYCLINGSTATEMACHINE_H

#include <functional>
#include <type_traits>

class CyclingStateMachineInterface {
public:
  virtual void next() = 0;
  virtual void reset() = 0;
};

template <class StateContainerType>
class CyclingStateMachine : public CyclingStateMachineInterface {
private:
  const StateContainerType *states;
  typename StateContainerType::const_iterator currentState;
  std::function<void(decltype(*currentState))> notificationReceiver;

public:
  CyclingStateMachine() {}

  void setStates(const StateContainerType &states) {
    this->states = &states;
    currentState = this->states->cbegin();
  }

  // const StateType &current() const { return *currentState; }

  void setCallback(
      std::function<void(decltype(*currentState))> notificationReceiver) {
    this->notificationReceiver = notificationReceiver;
  }

  virtual void next() override {
    ++currentState;
    if (currentState == states->cend())
      currentState = states->cbegin();
    if (notificationReceiver)
      notificationReceiver(*currentState);
  }

  virtual void reset() override {
    currentState = states->cbegin();
    if (notificationReceiver)
      notificationReceiver(*currentState);
  }
};

#endif // CYCLINGSTATEMACHINE_H
