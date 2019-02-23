#include "pwmwebserver.h"


PwmWebServer::PwmWebServer()
{
}

#include "gpiopwm.h"
GpioPWM gpiopwm;

void onAjaxLight(HttpRequest& request, HttpResponse& response)
{
	if (request.method == HTTP_POST) {
		StaticJsonBuffer<200> jsonBuffer;
		JsonObject& root = jsonBuffer.parseObject(request.getBody());
        for (size_t i = 0; i < root["pwm"].asArray().size(); ++i) {
            gpiopwm.setDuty(i, (uint32)root["pwm"][i]);
        }
	}
    response.sendString("");
}

void PwmWebServer::init()
{
	server.listen(80);
    server.addPath("/ajax/light", onAjaxLight);
    server.setBodyParser(ContentType::toString(MIME_JSON), bodyToStringParser);
//	server.setDefaultHandler(onFile);
}
