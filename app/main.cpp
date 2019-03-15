#include "buttontimer.h"
#include "cyclingStateMachine.h"
#include "cyclingbuttoneventhandler.h"
#include "gpiopwm.h"
#include "pwmwebserver.h"
#include <user_config.h>
#include <vector>

static const char *WIFI_SSID = "username"; // Put you SSID and Password here
static const char *WIFI_PWD = "password";

GpioPWM gpioPWM;
PwmWebServer pwmWebServer(gpioPWM);
CyclingStateMachine<std::vector<uint32>> states;
CyclingButtonEventHandler buttonEventHandler(states);
ButtonTimer buttonHandler(buttonEventHandler);

std::vector<uint32> stateDescription;
void gotIP(IPAddress ip, IPAddress netmask, IPAddress gateway) {
  pwmWebServer.init();

  Serial.println("\r\n=== WEB SERVER STARTED ===");
  Serial.println(ip);
  Serial.println("==============================\r\n");
}

void init() {
  // SystemClass().setCpuFrequency(eCF_160MHz);
  Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
  Serial.systemDebugOutput(true); // Enable debug output to serial

  spiffs_mount(); // Mount file system, in order to work with files
  WifiStation.enable(true);
  WifiStation.config(WIFI_SSID, WIFI_PWD);
  WifiAccessPoint.enable(false);
  WifiEvents.onStationGotIP(gotIP);
  stateDescription = {0, 20, 500, 1000};
  states.setStates(stateDescription);
  states.setCallback(
      std::bind(&GpioPWM::setDuty, &gpioPWM, (uint8)0, std::placeholders::_1));
}
