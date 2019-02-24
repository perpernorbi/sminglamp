#ifndef PWMCHANNELANDDUTYCONSUMER_H
#define PWMCHANNELANDDUTYCONSUMER_H

class PwmChannelAndDutyConsumer {
public:
  virtual uint32 getDuty(uint8 channel) const = 0;
  virtual void setDuty(uint8 channel, uint32 duty) = 0;
  virtual uint8 getChannelCount() const = 0;
};

#endif // PWMCHANNELANDDUTYCONSUMER_H
