#ifndef GPIOPWM_H
#define GPIOPWM_H
#include "SmingCore/HardwarePWM.h"
#include "pwminterface.h"
#include <user_config.h>

template <uint8_t... pins_template>
class GpioPWM : public PwmInterface,
                PwmArrayInterface<sizeof...(pins_template)> {
public:
  using State = std::array<uint32, sizeof...(pins_template)>;
  using PinConfig = std::array<uint8_t, sizeof...(pins_template)>;

private:
  HardwarePWM *HW_pwm;
  static constexpr PinConfig pins{pins_template...};

public:
  GpioPWM() {
    HW_pwm = new HardwarePWM(pins.data(), pins.size());
    HW_pwm->setPeriod(102);
    debugf("pwm initialized. Max duty: %d", HW_pwm->getMaxDuty());
    for (auto &pinNumber : pins)
      HW_pwm->analogWrite(pinNumber, 0);
  }

  virtual ~GpioPWM() { delete HW_pwm; }

  uint32 getDuty(uint8 channel) const override {
    return HW_pwm->getDuty(pins[channel]);
  }

  void setDuty(uint8 channel, uint32 duty) override {
    if (channel >= pins.size()) {
      debug_e("Channel number %u exeeds configured channel count %u", channel,
              pins.size());
      return;
    }
    if (duty > HW_pwm->getMaxDuty()) {
      debug_w("Trying to set duty to %u, while max duty is %u", duty,
              HW_pwm->getMaxDuty());
      duty = HW_pwm->getMaxDuty();
    }
    HW_pwm->analogWrite(pins[channel], duty);
  }

  void setDuty(const State &state) {
    for (size_t i = 0; i < state.size(); ++i)
      setDuty(i, state[i]);
  }

  State getDuty() { return {HW_pwm->getDuty(pins_template)...}; }

  uint8 getChannelCount() const { return pins.size(); }
};

template <uint8_t... pins_template>
typename GpioPWM<pins_template...>::PinConfig constexpr GpioPWM<
    pins_template...>::pins;

#endif // GPIOPWM_H
