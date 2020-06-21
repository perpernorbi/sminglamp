#include "JsonArrayStream.h"

void JsonArrayStream::getData() {
  if (send && rootNode.success()) {
    rootNode.printTo(*this);
    send = false;
  }
}

uint16_t JsonArrayStream::readMemoryBlock(char *data, int bufSize) {
  getData();
  return MemoryDataStream::readMemoryBlock(data, bufSize);
}

int JsonArrayStream::available() {
  getData();
  return rootNode.success() ? rootNode.measureLength() : 0;
}

bool JsonArrayStream::isFinished() {
  getData();
  return MemoryDataStream::isFinished();
}
