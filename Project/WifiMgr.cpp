#include "WifiMgr.h"

#include "Serial.h"
#include "NetworkInclude.h"
#include "Storage.h"

WifiMgr::WifiCredentials espApCredentials{ 0 };
Storage::StorageEntry espApCredentialsStorageEntry{ 0 };

WifiMgr::WifiCredentials wifiConnectCredentials{ 0 };
unsigned long wifiConnectTimeout = 0;
volatile bool wifiConnectLock = false;
volatile bool startWifiConnection = false;

void TaskConnectWifi(void* args) {
  while (true) {
    if (startWifiConnection) {
      startWifiConnection = false;
      while (wifiConnectLock) { taskYIELD(); }
      wifiConnectLock = true;
      WifiMgr::WifiCredentials credentials = wifiConnectCredentials;
      unsigned long timeout = wifiConnectTimeout;
      wifiConnectLock = false;

      SERIAL_PRINTF("Connection to ssid : \'%s\'. password : \'%s\'.", credentials.ssid, credentials.password);

      WiFi.begin((const char*)credentials.ssid, (const char*)credentials.password);
      unsigned long startingTime = millis();

      while (startingTime + timeout > millis()) {
        SERIAL_PRINT(".");

        if (WiFi.status() == WL_CONNECTED) {
          SERIAL_PRINTLN("Connected to WIFI successfully.");
          Storage::StorageEntry credentialsStorageEntry = Storage::CreateEntry(ESP_AUTO_CONNECT_STORAGE_ENTRY_NAME, sizeof(WifiMgr::WifiCredentials));
          Storage::Write(credentialsStorageEntry, (char*)&credentials, sizeof(WifiMgr::WifiCredentials));
          goto end;
        }

        vTaskDelay(500 / portTICK_PERIOD_MS);
      }

      WiFi.disconnect();
      SERIAL_PRINT("failed!\n");
    }
    end:
    taskYIELD();
  }
}

void WifiMgr::Init()
{
  xTaskCreate(TaskConnectWifi, "WifiConnectTask", 4096, NULL, tskIDLE_PRIORITY, NULL);

  if (!Storage::Exists(ESP_AP_STORAGE_ENTRY_NAME)) {
    espApCredentialsStorageEntry = Storage::CreateEntry(ESP_AP_STORAGE_ENTRY_NAME, sizeof(WifiCredentials));
    SERIAL_PRINTF("Access Point Credentials not found. Creating new one. Address : %d, Size : %d\n", espApCredentialsStorageEntry.address, espApCredentialsStorageEntry.size);
    memcpy(espApCredentials.ssid, DEFAULT_AP_SSID, sizeof(DEFAULT_AP_SSID));
    memcpy(espApCredentials.password, DEFAULT_AP_PASSWORD, sizeof(DEFAULT_AP_PASSWORD));
    Storage::Write(espApCredentialsStorageEntry, (char*)&espApCredentials, sizeof(WifiCredentials));
  } else {
    espApCredentialsStorageEntry = Storage::OpenEntry(ESP_AP_STORAGE_ENTRY_NAME);
    SERIAL_PRINTF("Access Point Credentials found. Address : %d, Size : %d\n", espApCredentialsStorageEntry.address, espApCredentialsStorageEntry.size);
    Storage::Read(espApCredentialsStorageEntry, (char*)&espApCredentials, sizeof(WifiCredentials));
  }

  SERIAL_PRINTF("AP SSID : \'%s\'\nAP Password : \'%s\'\n", espApCredentials.ssid, espApCredentials.password);

  WiFi.mode(WIFI_AP_STA);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  WiFi.softAP((const char*)espApCredentials.ssid, (const char*)espApCredentials.password);
  WiFi.softAPConfig(IPAddress{ 192, 168, 1, 1 }, IPAddress{ 10, 1, 1, 3 }, IPAddress{ 255, 255, 255, 0 });

  SERIAL_PRINT("AP Ip address : ");
  SERIAL_PRINTLN(WiFi.softAPIP());

  if (Storage::Exists(ESP_AUTO_CONNECT_STORAGE_ENTRY_NAME)) {
    WifiCredentials espAutoConnectCredentials{ 0 };
    Storage::StorageEntry espAutoConnectCredentialsStorageEntry = Storage::OpenEntry(ESP_AUTO_CONNECT_STORAGE_ENTRY_NAME);
    Storage::Read(espAutoConnectCredentialsStorageEntry, (char*)&espAutoConnectCredentials, sizeof(WifiCredentials));
    SERIAL_PRINTLN("Auto connect credentials found.");
    Connect(espAutoConnectCredentials);
  }
}

void WifiMgr::Connect(WifiCredentials credentials, unsigned long timeout) {
  while (wifiConnectLock) { taskYIELD(); }
  wifiConnectLock = true;
  wifiConnectCredentials = credentials;
  wifiConnectTimeout = timeout;
  wifiConnectLock = false;
  startWifiConnection = true;
}

int WifiMgr::ScanNetworks(WifiScanEntry* buff, size_t size) {
  SERIAL_PRINTLN("Scanning networks.");

  int n = WiFi.scanNetworks();
  n = size > n ? n : size;
  for (int i = 0; i < n; ++i) {
    memcpy(buff[i].ssid, WiFi.SSID(i).c_str(), 33);
    buff[i].rssi = WiFi.RSSI(i);
  }
  return n;
}

bool WifiMgr::IsConnected() {
  return WiFi.status() == WL_CONNECTED;
}

String WifiMgr::GetConnectedWifiSSID() {
  return WiFi.SSID();
}

WifiMgr::WifiCredentials WifiMgr::GetAPCredentials() {
  return espApCredentials;
}