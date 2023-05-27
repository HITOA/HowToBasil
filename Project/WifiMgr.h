#ifndef WIFIMGR_HEADER
#define WIFIMGR_HEADER

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

  void Init();
  bool Connect(WifiCredentials credentials, unsigned long timeout = DEFAULT_TIMEOUT_CONNECTION_VALUE);
}

#endif