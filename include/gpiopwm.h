#ifndef GPIOPWM_H
#define GPIOPWM_H
#include "SmingCore/HardwarePWM.h"
#include "pwmchannelanddutyconsumer.h"
#include <user_config.h>
//#include <stdint.h>

class GpioPWM : public PwmChannelAndDutyConsumer {
private:
  static const uint8_t pins[];
  static const size_t pinCount;
  HardwarePWM *HW_pwm;

public:
  GpioPWM();
  ~GpioPWM();

  void setDuty(uint8 pin, uint32 duty);
};

#endif // GPIOPWM_H
