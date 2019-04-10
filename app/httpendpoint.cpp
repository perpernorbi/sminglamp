#include "httpendpoint.h"

HttpEndpoint::HttpEndpoint(const String &endpoint)
    : endpoint(endpoint),
      httpPathDelegate(&HttpEndpoint::requestDispatcher, this) {}

HttpEndpoint::~HttpEndpoint() {}

const String &HttpEndpoint::getEndpoint() const { return endpoint; }

HttpEndpoint::operator const HttpPathDelegate &() const {
  return httpPathDelegate;
}

void HttpEndpoint::requestDispatcher(HttpRequest &request,
                                     HttpResponse &response) {
  response.code = HTTP_STATUS_INTERNAL_SERVER_ERROR;
  bool success;
  switch (request.method) {
  case HTTP_DELETE:
    success = requestDelete(request, response);
    break;
  case HTTP_GET:
    success = requestHead(request, response);
    if (success)
      success = requestGet(request, response);
    break;
  case HTTP_HEAD:
    success = requestHead(request, response);
    break;
  case HTTP_POST:
    success = requestPost(request, response);
    break;
  case HTTP_PUT:
    success = requestPut(request, response);
    break;
  default:
    responseMethodNotAllowed(response);
  }
}

bool HttpEndpoint::requestDelete(HttpRequest &request, HttpResponse &response) {
  responseMethodNotAllowed(response);
}

bool HttpEndpoint::requestGet(HttpRequest &request, HttpResponse &response) {
  responseMethodNotAllowed(response);
}

bool HttpEndpoint::requestHead(HttpRequest &request, HttpResponse &response) {
  responseMethodNotAllowed(response);
}

bool HttpEndpoint::requestPost(HttpRequest &request, HttpResponse &response) {
  responseMethodNotAllowed(response);
}

bool HttpEndpoint::requestPut(HttpRequest &request, HttpResponse &response) {
  responseMethodNotAllowed(response);
}

void HttpEndpoint::responseMethodNotAllowed(HttpResponse &response) {
  response.code = HTTP_STATUS_METHOD_NOT_ALLOWED;
  response.sendString("Method not allowed");
}
