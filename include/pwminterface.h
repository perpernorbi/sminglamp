#ifndef PWMCHANNELANDDUTYCONSUMER_H
#define PWMCHANNELANDDUTYCONSUMER_H

#include <array>
#include <c_types.h>

class PwmInterface {
public:
  virtual ~PwmInterface() {}
  virtual uint32 getDuty(uint8 channel) const = 0;
  virtual void setDuty(uint8 channel, uint32 duty) = 0;
  virtual uint8 getChannelCount() const = 0;
};

template <size_t channelCount, typename duty_t = uint32>
class PwmArrayInterface {
public:
  using State = std::array<duty_t, channelCount>;
  virtual ~PwmArrayInterface() {}
  virtual void setDuty(const State &state) = 0;
  virtual State getDuty() = 0;
};
#endif // PWMCHANNELANDDUTYCONSUMER_H
