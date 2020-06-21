#include "pwmwebserver.h"
#include "JsonArrayStream.h"
#include "gpiopwm.h"

PwmWebServer::PwmWebServer(PwmInterface &pwm)
    : pwm(pwm), testEndpoint("/test"),
      endpointChannelCount("/ajax/pwm/channelCount"),
      endpointTest("/ajax/test"), endpointSetBool("/ajax/setBool"),
      endpointSetInt("/ajax/setInt"), endpointSetString("/ajax/setString") {
  endpointChannelCount.setCallback([&pwm]() { return pwm.getChannelCount(); });
  endpointTest.setCallback([this]() { return this->get_a_vector(); });
  endpointSetBool.setCallback(
      [](bool value) { debugf("got %s", value ? "true" : "false"); });
  endpointSetInt.setCallback([](int value) { debugf("got %d", value); });
  endpointSetString.setCallback(
      [](const String &value) { debugf("got %s", value.c_str()); });
}

void PwmWebServer::onAjaxAsArray(HttpRequest &request, HttpResponse &response) {
  debugf("start");
  if (request.method == HTTP_GET) {
    auto *jsonArrayStream = new JsonArrayStream();
    auto &array = jsonArrayStream->getRoot();
    for (size_t i = 0; i < pwm.getChannelCount(); ++i)
      array.add(pwm.getDuty(i));
    response.sendDataStream(jsonArrayStream, ContentType::toString(MIME_JSON));
  } else if (request.method == HTTP_POST) {
    StaticJsonBuffer<200> jsonBuffer;
    auto &root = jsonBuffer.parseArray(request.getBody());
    for (size_t i = 0; i < root.size(); ++i) {
      pwm.setDuty(i, static_cast<uint32>(root[i]));
    }
    response.sendString("");
    response.code = 200;
  }
}

std::array<int, 3> PwmWebServer::get_a_vector() {
  std::array<int, 3> ret;
  ret[0] = 1;
  ret[1] = 2;
  ret[2] = 3;
  for (auto &i : ret) {
    debugf("get_a_vector %d", i);
  }
  return ret;
}

void PwmWebServer::init() {
  server.listen(80);
  server.paths.set("/ajax/pwm/asArray",
                   HttpPathDelegate(&PwmWebServer::onAjaxAsArray, this));
  server.paths.set(endpointChannelCount.getEndpoint(), endpointChannelCount);
  server.paths.set(testEndpoint.getEndpoint(), testEndpoint);
  server.paths.set(endpointTest.getEndpoint(), endpointTest);
  server.paths.set(endpointSetBool.getEndpoint(), endpointSetBool);
  server.paths.set(endpointSetInt.getEndpoint(), endpointSetInt);
  server.paths.set(endpointSetString.getEndpoint(), endpointSetString);
  server.setBodyParser(ContentType::toString(MIME_JSON), bodyToStringParser);
  //	server.setDefaultHandler(onFile);
}
