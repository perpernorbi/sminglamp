#include "button.h"
#include "cyclingStateMachine.h"
#include "gpiopwm.h"
#include "pwmwebserver.h"
#include "ws2812pwm.h"
#include <user_config.h>

static const char *WIFI_SSID = "norbi"; // Put you SSID and Password here
static const char *WIFI_PWD = "S3ful3.3f4rk4";
// static const char *WIFI_SSID = "norbert"; // Put you SSID and Password here
// static const char *WIFI_PWD = "internet";

// using GpioPWM_t = GpioPWM<2, 15, 13, 12>;
// static GpioPWM_t gpioPWM;
// static PwmWebServer pwmWebServer(gpioPWM);
// static CyclingStateMachine<std::vector<GpioPWM_t::State>> states;

static Ws2812PWM<2, 6> ws2812;
static PwmWebServer pwmWebServer(ws2812);

/*static const struct Button::Event shortPress(Button::State::pressedFor, 0,
500,
                                             [](int i) { states.next(); });

static const struct Button::Event resetPress(Button::State::pressingSince, 1500,
                                             1500,
                                             [](int i) { states.reset(); });

static const Button::ButtonTimer<0, 50, &shortPress, &resetPress> buttonTimer;
*/

// static std::vector<GpioPWM_t::State> stateDescription;

static void STAGotIP(IpAddress ip, IpAddress mask, IpAddress gateway) {
  debugf("GOTIP - IP: %s, MASK: %s, GW: %s\n", ip.toString().c_str(),
         mask.toString().c_str(), gateway.toString().c_str());
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
  WifiEvents.onStationGotIP(STAGotIP);
  /*  stateDescription = {{0, 0, 0, 0},
                        {2500, 0, 0, 0},
                        {0, 2500, 0, 0},
                        {0, 0, 2500, 0},
                        {0, 0, 0, 2500}};
    states.setStates(stateDescription);

    states.setCallback(
        std::bind(static_cast<void (GpioPWM_t::*)(const GpioPWM_t::State &)>(
                      &GpioPWM_t::setDuty),
                  &gpioPWM, std::placeholders::_1));*/
}
