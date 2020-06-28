#pragma once

#include "pwminterface.h"

#include <SmingCore.h>

template <uint8_t pin, uint8_t pixelcount>
class Ws2812PWM : public PwmInterface, PwmArrayInterface<pixelcount * 3, char> {
public:
  using State = typename PwmArrayInterface<pixelcount * 3, char>::State;

private:
  State state;
  static constexpr int gpio = 1 << pin;

  void writePixels() {
    noInterrupts();
    for (int i = 0; i < state.size(); ++i) {
      const uint8_t value = state[i];
      uint8_t mask = 0x80;
      while (mask) {
        uint8_t up = (value & mask) ? 7 : 1;
        uint8_t down = (value & mask) ? 5 : 9;
        while (up--)
          GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, gpio);
        while (down--)
          GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, gpio);

        mask >>= 1;
      }
    }
    interrupts();
  }

public:
  Ws2812PWM() {
    pinMode(pin, OUTPUT);
    GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, gpio);
    os_delay_us(10);
    state.fill(0);
    writePixels();
  }

  virtual uint32 getDuty(uint8 channel) const override {
    return state[channel];
  }

  virtual void setDuty(uint8 channel, uint32 duty) override {
    // WS2812 uses GRB ordering
    const size_t corrected_index = [](int i) {
      switch (i % 3) {
      case 0:
        return i + 1;
      case 1:
        return i - 1;
      case 2:
        return i;
      }
      return 0;
    }(channel);
    state[corrected_index] = duty;
    // if (channel == (pixelcount * 3 - 1))
    writePixels();
  }

  virtual void setDuty(const State &state) override {
    this->state = state;
    writePixels();
  }

  virtual State getDuty() override { return state; }

  virtual uint8 getChannelCount() const override { return pixelcount * 3; }
};
