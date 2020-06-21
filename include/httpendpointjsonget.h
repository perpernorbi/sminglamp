#ifndef HTTPENDPOINTJSONGET_H
#define HTTPENDPOINTJSONGET_H
#include "httpendpoint.h"
#include "jsonconverter.h"
#include <functional>

template <typename T> class HttpEndpointJsonGet : public HttpEndpoint {
public:
  using callback_t = std::function<const T(void)>;
  HttpEndpointJsonGet(const String &endpoint) : HttpEndpoint(endpoint) {}
  virtual ~HttpEndpointJsonGet() {}

  void setCallback(callback_t callback) { this->callback = callback; }

private:
  callback_t callback;

protected:
  virtual bool requestHead(HttpRequest &request,
                           HttpResponse &response) override {
    debugf("requestHead");
    if (!callback)
      return false;
    response.code = HTTP_STATUS_OK;
    response.setContentType(ContentType::toString(MIME_JSON));
    return true;
  }

  virtual bool requestGet(HttpRequest &request,
                          HttpResponse &response) override {
    debugf("requestGet");
    const T &value = callback();
    auto *jsonStream = JsonConverter::toJson<T>(value);
    return response.sendDataStream(jsonStream);
  }
};
#endif // HTTPENDPOINTJSONGET_H
