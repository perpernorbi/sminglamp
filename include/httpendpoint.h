#ifndef HTTPENDPOINT_H
#define HTTPENDPOINT_H
#include <Network/Http/HttpResourceTree.h>

class HttpEndpoint {
private:
  String endpoint;
  HttpPathDelegate httpPathDelegate;

public:
  HttpEndpoint(const String &endpoint);
  virtual ~HttpEndpoint();

  const String &getEndpoint() const;
  operator const HttpPathDelegate &() const;

  virtual void requestDispatcher(HttpRequest &request, HttpResponse &response);

protected:
  virtual bool requestDelete(HttpRequest &request, HttpResponse &response);
  virtual bool requestGet(HttpRequest &request, HttpResponse &response);
  virtual bool requestHead(HttpRequest &request, HttpResponse &response);
  virtual bool requestPost(HttpRequest &request, HttpResponse &response);
  virtual bool requestPut(HttpRequest &request, HttpResponse &response);

private:
  bool responseMethodNotAllowed(HttpResponse &response);
};
#endif // HTTPENDPOINT_H
