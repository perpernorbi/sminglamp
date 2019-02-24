#ifndef GPIOPWM_H
#define GPIOPWM_H
#include "SmingCore/HardwarePWM.h"
#include "pwminterface.h"
#include <user_config.h>
//#include <stdint.h>

class GpioPWM : public PwmInterface {
private:
  static const uint8_t pins[];
  static const size_t pinCount;
  HardwarePWM *HW_pwm;

public:
  GpioPWM();
  ~GpioPWM();

  uint32 getDuty(uint8 channel) const;
  void setDuty(uint8 channel, uint32 duty);
  uint8 getChannelCount() const;
};

#endif // GPIOPWM_H
