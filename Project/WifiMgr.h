#ifndef WIFIMGR_HEADER
#define WIFIMGR_HEADER

#include <cstddef>
#include <arduino.h>

#define ESP_AP_STORAGE_ENTRY_NAME "esp-ap-credentials"
#define ESP_AUTO_CONNECT_STORAGE_ENTRY_NAME "esp-auto-connect-credentials"

#define DEFAULT_AP_SSID "HowToBasil Access Point"
#define DEFAULT_AP_PASSWORD "12345678"

#define DEFAULT_TIMEOUT_CONNECTION_VALUE 10000UL

namespace WifiMgr
{
  struct WifiCredentials {
    char ssid[33];
    char password[64];
  };

  struct WifiScanEntry {
    char ssid[33];
    int rssi;
  };

  void Init();
  void Connect(WifiCredentials credentials, unsigned long timeout = DEFAULT_TIMEOUT_CONNECTION_VALUE);
  int ScanNetworks(WifiScanEntry* buff, size_t size);
  bool IsConnected();
  String GetConnectedWifiSSID();
  WifiCredentials GetAPCredentials();
}

#endif