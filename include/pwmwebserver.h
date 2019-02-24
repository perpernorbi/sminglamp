#ifndef PWMWEBSERVER_H
#define PWMWEBSERVER_H
#include "pwmchannelanddutyconsumer.h"
#include <SmingCore/SmingCore.h>

class PwmWebServer {
public:
  PwmWebServer(PwmChannelAndDutyConsumer &pwm);
  void init();
  void onAjaxAsArray(HttpRequest &request, HttpResponse &response);
  void onAjaxGetChannelCount(HttpRequest &request, HttpResponse &response);

private:
  HttpServer server;
  PwmChannelAndDutyConsumer &pwm;
};

#endif // PWMWEBSERVER_H
