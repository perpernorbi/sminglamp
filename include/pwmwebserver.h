#ifndef PWMWEBSERVER_H
#define PWMWEBSERVER_H
#include "pwminterface.h"
#include <SmingCore/SmingCore.h>

class PwmWebServer {
public:
  PwmWebServer(PwmInterface &pwm);
  void init();
  void onAjaxAsArray(HttpRequest &request, HttpResponse &response);
  void onAjaxGetChannelCount(HttpRequest &request, HttpResponse &response);

private:
  HttpServer server;
  PwmInterface &pwm;
};

#endif // PWMWEBSERVER_H
