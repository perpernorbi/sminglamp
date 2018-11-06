#include <user_config.h>
#include "pwmwebserver.h"


static const char* WIFI_SSID = "username"; // Put you SSID and Password here
static const char* WIFI_PWD = "password";

PwmWebServer pwmWebServer;


void gotIP(IPAddress ip, IPAddress netmask, IPAddress gateway)
{
    pwmWebServer.init();

	Serial.println("\r\n=== WEB SERVER STARTED ===");
	Serial.println(ip);
	Serial.println("==============================\r\n");
}

void init()
{
	//SystemClass().setCpuFrequency(eCF_160MHz);
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true); // Enable debug output to serial

	spiffs_mount(); // Mount file system, in order to work with files
	WifiStation.enable(true);
	WifiStation.config(WIFI_SSID, WIFI_PWD);
	WifiAccessPoint.enable(false);
	WifiEvents.onStationGotIP(gotIP);
}
