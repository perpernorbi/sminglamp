#ifndef PWMWEBSERVER_H
#define PWMWEBSERVER_H
#include <SmingCore/SmingCore.h>

class PwmWebServer {
public:
  PwmWebServer();
  void init();

private:
  HttpServer server;
};

#endif // PWMWEBSERVER_H
