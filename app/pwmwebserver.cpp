#include "pwmwebserver.h"


PwmWebServer::PwmWebServer()
{
}

#include "gpiopwm.h"
GpioPWM gpiopwm;

void onAjaxLight(HttpRequest& request, HttpResponse& response)
{
	debugf("onAjaxLight");
    debugf("path: %s", request.uri.Path.c_str());
	if (request.method == HTTP_POST) {
		debugf("POST");
		debugf("%s", request.getHeader("content-type").c_str());
        //debugf("HEADER: \"%s\"\n", request.getHeader());
		StaticJsonBuffer<200> jsonBuffer;
		JsonObject& root = jsonBuffer.parseObject(request.getBody());
		root.prettyPrintTo(Serial);
        for (size_t i = 0; i < root["pwm"].asArray().size(); ++i) {
			debugf("%d, %d", i, (uint32)root["pwm"][i]);
            gpiopwm.setDuty(i, (uint32)root["pwm"][i]);
        }
		//int pwm = ((uint32)root["pwm"])*10;
		//debugf("pwm = %d", pwm);
        //HW_pwm.analogWrite(2, pwm);
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
