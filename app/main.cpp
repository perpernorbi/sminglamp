#include "button.h"
#include "cyclingStateMachine.h"
#include "gpiopwm.h"
#include "pwmwebserver.h"
#include <user_config.h>
#include <vector>

static const char *WIFI_SSID = "username"; // Put you SSID and Password here
static const char *WIFI_PWD = "password";

static GpioPWM gpioPWM;
static PwmWebServer pwmWebServer(gpioPWM);
static CyclingStateMachine<std::vector<uint32>> states;

static const struct Button::Event shortPress(Button::State::pressedFor, 0, 500,
                                             [](int i) { states.next(); });

static const struct Button::Event resetPress(Button::State::pressingSince, 1500,
                                             1500,
                                             [](int i) { states.reset(); });

static const Button::ButtonTimer<0, 50, &shortPress, &resetPress> buttonTimer;
static std::vector<uint32> stateDescription;

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
  stateDescription = {0, 20, 500, 1000, 2500};
  states.setStates(stateDescription);
  states.setCallback(
      std::bind(&GpioPWM::setDuty, &gpioPWM, (uint8)0, std::placeholders::_1));
}
