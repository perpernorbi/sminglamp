#ifndef _SMING_CORE_DATA_JSON_VARIANT_STREAM_H_
#define _SMING_CORE_DATA_JSON_VARIANT_STREAM_H_

#include <Data/Stream/MemoryDataStream.h>
#include <Libraries/ArduinoJson5/include/ArduinoJson.h>

class JsonVariantStream : public MemoryDataStream {
public:
  JsonVariantStream(JsonVariant rootNode) : rootNode(rootNode) {}

  virtual ~JsonVariantStream() = default;

  virtual StreamType getStreamType() const override { return eSST_JsonObject; }

  JsonVariant &getRoot() { return rootNode; }

  virtual uint16_t readMemoryBlock(char *data, int bufSize) override;

  virtual int available() override;

  virtual bool isFinished() override;

private:
  void getData();
  DynamicJsonBuffer buffer;
  JsonVariant rootNode;
  bool send = true;
};

#endif /* _SMING_CORE_DATA_JSON_VARIANT_STREAM_H_ */
