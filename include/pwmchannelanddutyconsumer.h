#ifndef PWMCHANNELANDDUTYCONSUMER_H
#define PWMCHANNELANDDUTYCONSUMER_H

class PwmChannelAndDutyConsumer {
public:
  virtual void setDuty(uint8 pin, uint32 duty) = 0;
};

#endif // PWMCHANNELANDDUTYCONSUMER_H
