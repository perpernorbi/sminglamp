/****
 * Sming Framework Project - Open Source framework for high efficiency native
 *ESP8266 development. Created 2015 by Skurydin Alexey
 * http://github.com/anakod/Sming
 * All files of the Sming Core are provided under the LGPL v3 license.
 ****/

#include "JsonArrayStream.h"

uint16_t JsonArrayStream::readMemoryBlock(char *data, int bufSize) {
  if (send && rootNode.success()) {
    rootNode.printTo(*this);
    send = false;
  }

  return MemoryDataStream::readMemoryBlock(data, bufSize);
}