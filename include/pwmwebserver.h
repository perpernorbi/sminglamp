#ifndef PWMWEBSERVER_H
#define PWMWEBSERVER_H
#include "httpendpoint.h"
#include "httpendpointjsonget.h"
#include "httpendpointjsonset.h"
#include "pwminterface.h"
#include <SmingCore.h>
#include <array>
#include <vector>

class PwmWebServer {
public:
  PwmWebServer(PwmInterface &pwm);
  void init();
  void onAjaxAsArray(HttpRequest &request, HttpResponse &response);

private:
  HttpServer server;
  PwmInterface &pwm;
  HttpEndpoint testEndpoint;
  HttpEndpointJsonGet<unsigned int> endpointChannelCount;
  HttpEndpointJsonGet<std::array<int, 3>> endpointTest;
  HttpEndpointJsonSet<bool> endpointSetBool;
  HttpEndpointJsonSet<int> endpointSetInt;
  HttpEndpointJsonSet<String> endpointSetString;
  std::array<int, 3> get_a_vector();
};

#endif // PWMWEBSERVER_H
