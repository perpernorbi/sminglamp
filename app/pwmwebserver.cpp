#include "pwmwebserver.h"
#include "gpiopwm.h"

PwmWebServer::PwmWebServer() {}

GpioPWM gpiopwm;

void onAjaxAsArray(HttpRequest &request, HttpResponse &response) {
  if (request.method == HTTP_GET) {
    JsonObjectStream *jsonObjectStream = new JsonObjectStream();
    auto &root = jsonObjectStream->getRoot();
    auto &pwm = root.createNestedArray("pwm");
    for (size_t i = 0; i < gpiopwm.getChannelCount(); ++i)
      pwm.add(gpiopwm.getDuty(i));
    response.sendDataStream(jsonObjectStream, ContentType::toString(MIME_JSON));
  } else if (request.method == HTTP_POST) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(request.getBody());
    for (size_t i = 0; i < root["pwm"].asArray().size(); ++i) {
      gpiopwm.setDuty(i, (uint32)root["pwm"][i]);
    }
    response.sendString("");
  }
}

void onAjaxGetChannelCount(HttpRequest &request, HttpResponse &response) {
  if (request.method == HTTP_GET) {
    JsonObjectStream *jsonObjectStream = new JsonObjectStream();
    auto &root = jsonObjectStream->getRoot();
    root["channelCount"] = gpiopwm.getChannelCount();
    response.sendDataStream(jsonObjectStream, ContentType::toString(MIME_JSON));
  }
}

void PwmWebServer::init() {
  server.listen(80);
  server.addPath("/ajax/pwm/asArray", onAjaxAsArray);
  server.addPath("/ajax/pwm/channelCount", onAjaxGetChannelCount);
  server.setBodyParser(ContentType::toString(MIME_JSON), bodyToStringParser);
  //	server.setDefaultHandler(onFile);
}
