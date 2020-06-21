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
  bool success = false;
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
    success = responseMethodNotAllowed(response);
  }
  if (!success) {
    response.code = HTTP_STATUS_INTERNAL_SERVER_ERROR;
  }
}

bool HttpEndpoint::requestDelete(HttpRequest &request, HttpResponse &response) {
  responseMethodNotAllowed(response);
  return false;
}

bool HttpEndpoint::requestGet(HttpRequest &request, HttpResponse &response) {
  responseMethodNotAllowed(response);
  return false;
}

bool HttpEndpoint::requestHead(HttpRequest &request, HttpResponse &response) {
  responseMethodNotAllowed(response);
  return false;
}

bool HttpEndpoint::requestPost(HttpRequest &request, HttpResponse &response) {
  responseMethodNotAllowed(response);
  return false;
}

bool HttpEndpoint::requestPut(HttpRequest &request, HttpResponse &response) {
  responseMethodNotAllowed(response);
  return false;
}

bool HttpEndpoint::responseMethodNotAllowed(HttpResponse &response) {
  response.code = HTTP_STATUS_METHOD_NOT_ALLOWED;
  return response.sendString("Method not allowed");
}
