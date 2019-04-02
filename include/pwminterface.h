#ifndef PWMCHANNELANDDUTYCONSUMER_H
#define PWMCHANNELANDDUTYCONSUMER_H

#include <array>
#include <espinc/c_types_compatible.h>

class PwmInterface {
public:
  virtual uint32 getDuty(uint8 channel) const = 0;
  virtual void setDuty(uint8 channel, uint32 duty) = 0;
  virtual uint8 getChannelCount() const = 0;
};

template <size_t channelCount> class PwmArrayInterface {
  using State = std::array<uint32, channelCount>;
  virtual void setDuty(const State &state) = 0;
  virtual State getDuty() = 0;
};
#endif // PWMCHANNELANDDUTYCONSUMER_H
