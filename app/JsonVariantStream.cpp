#include "JsonVariantStream.h"

void JsonVariantStream::getData() {
  if (send && rootNode.success()) {
    rootNode.printTo(*this);
    send = false;
  }
}

uint16_t JsonVariantStream::readMemoryBlock(char *data, int bufSize) {
  getData();
  return MemoryDataStream::readMemoryBlock(data, bufSize);
}

int JsonVariantStream::available() {
  getData();
  return rootNode.success() ? rootNode.measureLength() : 0;
}

bool JsonVariantStream::isFinished() {
  getData();
  return MemoryDataStream::isFinished();
}
