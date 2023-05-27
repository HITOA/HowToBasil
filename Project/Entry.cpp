#include <arduino.h>
#include "ProjectConfig.h"
#include "Serial.h"
#include "Storage.h"
#include "WifiMgr.h"
#include "BasilWebServer.h"
#include "PhMgr.h"
#include "NutrientsMgr.h"
#include "Credentials.h"

void setup()
{
  SERIAL_INIT(SERIAL_BAUD_RATE);
  Storage::Init();
  SERIAL_PRINTF("Storage entry count : %d\n", Storage::GetEntryCount());

  WifiMgr::WifiCredentials credentials{ 0 };
  memcpy(credentials.ssid, SSID, sizeof(SSID));
  memcpy(credentials.password, PASSWORD, sizeof(PASSWORD));
  Storage::StorageEntry credentialsStorageEntry = Storage::CreateEntry(ESP_AUTO_CONNECT_STORAGE_ENTRY_NAME, sizeof(WifiMgr::WifiCredentials));
  Storage::Write(credentialsStorageEntry, (char*)&credentials, sizeof(WifiMgr::WifiCredentials));

  WifiMgr::Init();
  BasilWebServer::Setup();
}

void loop(void)
{
  //PhMgr::Update();
  //NutrientsMgr::Update();
  BasilWebServer::Update();
}
