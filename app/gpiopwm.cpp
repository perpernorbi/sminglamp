#include "gpiopwm.h"

const uint8_t GpioPWM::pins[] = {2, 15, 13, 12}; // List of pins that you want to connect to pwm
const size_t GpioPWM::pinCount = sizeof(pins) / sizeof(pins[0]);

GpioPWM::GpioPWM()
{
	HW_pwm = new HardwarePWM(pins, pinCount);
	HW_pwm->setPeriod(102);
    debugf("pwm initialized. Max duty: %d", HW_pwm->getMaxDuty());
	// Setting PWM values on 8 different pins
	HW_pwm->analogWrite(2, 0);
    HW_pwm->analogWrite(15, 0);
	HW_pwm->analogWrite(13, 0);
	HW_pwm->analogWrite(12, 0);
}

GpioPWM::~GpioPWM()
{
    delete HW_pwm;
}

void GpioPWM::setDuty(uint8 pin, uint32 duty)
{
    if (pin >= pinCount) {
        debug_e("Pin id %d exeeds configured pin count %d", pin, pinCount);
        return;
    }
    if (duty > HW_pwm->getMaxDuty()) {
        debug_w("Trying to set duty to %u, while max duty is %u", duty, HW_pwm->getMaxDuty());
        duty = HW_pwm->getMaxDuty();
    }
    HW_pwm->analogWrite(pins[pin], duty);
}
