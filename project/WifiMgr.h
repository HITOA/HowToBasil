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
    Serial.println("Connecting to wifi...");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}
