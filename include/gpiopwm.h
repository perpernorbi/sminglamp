#ifndef GPIOPWM_H
#define GPIOPWM_H
#include <user_config.h>
#include "SmingCore/HardwarePWM.h"
#include "pwmchannelanddutyconsumer.h"
//#include <stdint.h>

class GpioPWM : public PwmChannelAndDutyConsumer
{
private:
	static const uint8_t pins[];// = {2, 15, 13, 12}; // List of pins that you want to connect to pwm
	static const size_t pinCount;// = sizeof(pins) / sizeof(pins[0]);
	HardwarePWM* HW_pwm;

public:
    GpioPWM();
    ~GpioPWM();

    void setDuty(uint8 pin, uint32 duty);
};

#endif // GPIOPWM_H
