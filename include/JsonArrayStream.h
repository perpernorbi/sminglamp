/****
 * Sming Framework Project - Open Source framework for high efficiency native
 *ESP8266 development. Created 2015 by Skurydin Alexey
 * http://github.com/anakod/Sming
 * All files of the Sming Core are provided under the LGPL v3 license.
 ****/

#ifndef _SMING_CORE_DATA_JSON_ARRAY_STREAM_H_
#define _SMING_CORE_DATA_JSON_ARRAY_STREAM_H_

#include <Data/Stream/MemoryDataStream.h>
#include <Libraries/ArduinoJson5/include/ArduinoJson.h>

class JsonArrayStream : public MemoryDataStream {
public:
  JsonArrayStream() : rootNode(buffer.createArray()) {}

  virtual ~JsonArrayStream() = default;

  virtual StreamType getStreamType() const override { return eSST_JsonObject; }

  JsonArray &getRoot() { return rootNode; }

  virtual uint16_t readMemoryBlock(char *data, int bufSize) override;

  int available() override;

  bool isFinished() override;

private:
  void getData();
  DynamicJsonBuffer buffer;
  JsonArray &rootNode;
  bool send = true;
};

#endif /* _SMING_CORE_DATA_JSON_ARRAY_STREAM_H_ */
