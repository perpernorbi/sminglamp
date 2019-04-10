#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include "JsonVariantStream.h"
#include <SmingCore/Data/Stream/MemoryDataStream.h>

namespace JsonConverter {
template <typename T> ReadWriteStream *toJson(T value) {
  JsonVariant json(value);
  JsonVariantStream *stream = new JsonVariantStream(json);
  return stream;
}

} // namespace JsonConverter
#endif // JSONCONVERTER_H
