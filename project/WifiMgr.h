#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "Credentials.h"

namespace WifiMgr
{
  void SetupWifi()
  {
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    WiFi.begin(ssid, password);
  }

  void ConnectWifi()
  {
    SERIAL_PRINTLN("Connecting to wifi...");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      SERIAL_PRINT(".");
    }
    SERIAL_PRINTLN("");
    SERIAL_PRINT("Connected to ");
    SERIAL_PRINTLN(ssid);
    SERIAL_PRINT("IP address: ");
    SERIAL_PRINTLN(WiFi.localIP());
  }
}
