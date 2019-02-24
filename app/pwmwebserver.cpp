#include "pwmwebserver.h"
#include "gpiopwm.h"

PwmWebServer::PwmWebServer(PwmChannelAndDutyConsumer &pwm) : pwm(pwm) {}

void PwmWebServer::onAjaxAsArray(HttpRequest &request, HttpResponse &response) {
  if (request.method == HTTP_GET) {
    JsonObjectStream *jsonObjectStream = new JsonObjectStream();
    auto &root = jsonObjectStream->getRoot();
    auto &array = root.createNestedArray("pwm");
    for (size_t i = 0; i < pwm.getChannelCount(); ++i)
      array.add(pwm.getDuty(i));
    response.sendDataStream(jsonObjectStream, ContentType::toString(MIME_JSON));
  } else if (request.method == HTTP_POST) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(request.getBody());
    for (size_t i = 0; i < root["pwm"].asArray().size(); ++i) {
      pwm.setDuty(i, (uint32)root["pwm"][i]);
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
