#ifndef HTTPENDPOINTJSONGET_H
#define HTTPENDPOINTJSONGET_H
#include "httpendpoint.h"
#include "jsonconverter.h"
#include <functional>

template <typename T> class HttpEndpointJsonGet : public HttpEndpoint {
public:
  using callback_t = std::function<const T(void)>;
  HttpEndpointJsonGet(const String &endpoint, callback_t callback)
      : HttpEndpoint(endpoint), callback(callback) {}
  virtual ~HttpEndpointJsonGet() {}

private:
  callback_t callback;

protected:
  virtual bool requestHead(HttpRequest &request,
                           HttpResponse &response) override {
    response.code = HTTP_STATUS_OK;
    response.setContentType(ContentType::toString(MIME_JSON));
    return true;
  }

  virtual bool requestGet(HttpRequest &request,
                          HttpResponse &response) override {
    const T value = callback();
    auto *jsonStream = JsonConverter::toJson(value);
    response.sendDataStream(jsonStream);
    return true;
  }
};
#endif // HTTPENDPOINTJSONGET_H
