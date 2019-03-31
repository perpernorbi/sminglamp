#include "pwmwebserver.h"
#include "JsonArrayStream.h"
#include "gpiopwm.h"

PwmWebServer::PwmWebServer(PwmInterface &pwm) : pwm(pwm) {}

void PwmWebServer::onAjaxAsArray(HttpRequest &request, HttpResponse &response) {
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
  }
}

void PwmWebServer::onAjaxGetChannelCount(HttpRequest &request,
                                         HttpResponse &response) {
  if (request.method == HTTP_GET) {
    JsonObjectStream *jsonObjectStream = new JsonObjectStream();
    auto &root = jsonObjectStream->getRoot();
    root["channelCount"] = pwm.getChannelCount();
    response.sendDataStream(jsonObjectStream, ContentType::toString(MIME_JSON));
  }
}

void PwmWebServer::init() {
  server.listen(80);
  server.addPath("/ajax/pwm/asArray",
                 HttpPathDelegate(&PwmWebServer::onAjaxAsArray, this));
  server.addPath("/ajax/pwm/channelCount",
                 HttpPathDelegate(&PwmWebServer::onAjaxGetChannelCount, this));
  server.setBodyParser(ContentType::toString(MIME_JSON), bodyToStringParser);
  //	server.setDefaultHandler(onFile);
}
