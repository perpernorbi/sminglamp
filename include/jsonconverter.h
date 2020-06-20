#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include "JsonArrayStream.h"
#include "JsonVariantStream.h"
#include <Libraries/ArduinoJson/ArduinoJson.h>
#include <Libraries/ArduinoJson/include/ArduinoJson/Internals/JsonParser.hpp>
#include <Libraries/ArduinoJson/include/ArduinoJson/JsonBuffer.hpp>
#include <SmingCore/Data/Stream/MemoryDataStream.h>
#include <cstdlib>
#include <string.h>
#include <type_traits>

namespace JsonConverter {
// template <> ReadWriteStream *toJson<unsigned int>(unsigned int value);
namespace detail {
// To allow ADL with custom begin/end
using std::begin;
using std::end;

template <typename T>
auto is_iterable_impl(int) -> decltype(
    begin(std::declval<T &>()) !=
        end(std::declval<T &>()), // begin/end and operator !=
    //  void(),                       // Handle evil operator ,
    ++std::declval<decltype(begin(std::declval<T &>())) &>(), // operator ++
    void(*begin(std::declval<T &>())),                        // operator*
    std::true_type{});

template <typename T> std::false_type is_iterable_impl(...);
} // namespace detail

template <typename T>
using is_iterable = decltype(detail::is_iterable_impl<T>(0));

template <typename T>
ReadWriteStream *
toJson(const T &value,
       typename std::enable_if<!is_iterable<T>::value>::type * = 0) {
  JsonVariant json(value);
  JsonVariantStream *stream = new JsonVariantStream(json);
  return stream;
}

template <typename T>
ReadWriteStream *
toJson(const T &value,
       typename std::enable_if<is_iterable<T>::value>::type * = 0) {
  JsonArrayStream *jsonArrayStream = new JsonArrayStream;
  auto &root = jsonArrayStream->getRoot();
  for (const auto &i : value) {
    root.add(i);
    debugf("toJson %d", i);
  }
  return jsonArrayStream;
}

template <typename T>
bool fromJson(
    const String &in, T &out,
    typename std::enable_if<std::is_same<bool, T>::value>::type * = 0) {
  if (in == "true") {
    out = true;
    return true;
  }
  if (in == "false") {
    out = false;
    return true;
  }
  return false;
}

template <typename T>
bool fromJson(const String &in, T &out,
              typename std::enable_if<!std::is_same<bool, T>::value &&
                                      std::is_integral<T>::value>::type * = 0) {
  const char *str = in.c_str();
  char *endptr = NULL;
  out = std::strtol(str, &endptr, 10);
  return '\0' == *endptr;
}

template <typename T>
bool fromJson(
    const String &in, T &out,
    typename std::enable_if<std::is_same<String, T>::value>::type * = 0) {
  auto l = in.length();
  if ((l < 2) || (in[0] != '"') || (in[l - 1] != '"'))
    return false;
  out.setString(in.c_str() + 1, l - 2);
  return true;
}

} // namespace JsonConverter
#endif // JSONCONVERTER_H
