#include "gpiopwm.h"

// List of pins that you want to connect to pwm
const uint8_t GpioPWM::pins[] = {2, 15, 13, 12};
const size_t GpioPWM::pinCount = sizeof(pins) / sizeof(pins[0]);

GpioPWM::GpioPWM() {
  HW_pwm = new HardwarePWM(pins, pinCount);
  HW_pwm->setPeriod(102);
  debugf("pwm initialized. Max duty: %d", HW_pwm->getMaxDuty());
  for (auto &pinNumber : pins)
    HW_pwm->analogWrite(pinNumber, 0);
}

GpioPWM::~GpioPWM() { delete HW_pwm; }

void GpioPWM::setDuty(uint8 pin, uint32 duty) {
  if (pin >= pinCount) {
    debug_e("Pin id %d exeeds configured pin count %d", pin, pinCount);
    return;
  }
  if (duty > HW_pwm->getMaxDuty()) {
    debug_w("Trying to set duty to %u, while max duty is %u", duty,
            HW_pwm->getMaxDuty());
    duty = HW_pwm->getMaxDuty();
  }
  HW_pwm->analogWrite(pins[pin], duty);
}
