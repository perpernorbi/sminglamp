#ifndef HTTPENDPOINTJSONSET_H
#define HTTPENDPOINTJSONSET_H
#include "httpendpoint.h"
#include "jsonconverter.h"
#include <functional>

template <typename T> class HttpEndpointJsonSet : public HttpEndpoint {
public:
  using callback_t = std::function<void(T)>;
  HttpEndpointJsonSet(const String &endpoint) : HttpEndpoint(endpoint) {}
  virtual ~HttpEndpointJsonSet() {}

  void setCallback(callback_t callback) { this->callback = callback; }

private:
  callback_t callback;

protected:
  virtual bool requestPost(HttpRequest &request,
                           HttpResponse &response) override {
    if (!callback)
      return false;
    T value;
    bool success = JsonConverter::fromJson<T>(request.getBody(), value);
    if (!success) {
      response.code = HTTP_STATUS_BAD_REQUEST;
      response.sendString("Bad request");
      return false;
    }
    callback(value);
    response.code = HTTP_STATUS_OK;
    return true;
  }
};
#endif // HTTPENDPOINTJSONSET_H
