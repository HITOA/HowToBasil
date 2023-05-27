#include <arduino.h>
#include "ProjectConfig.h"
#include "Serial.h"
#include "Storage.h"
#include "WifiMgr.h"
#include "BasilWebServer.h"
#include "PhMgr.h"
#include "NutrientsMgr.h"

void setup()
{
  SERIAL_INIT(SERIAL_BAUD_RATE);
  Storage::Init();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  Serial.flush();

  WifiMgr::SetupWifi();
  WifiMgr::ConnectWifi();

  BasilWebServer::Setup();
}

void loop(void)
{
  PhMgr::Update();
  NutrientsMgr::Update();
  BasilWebServer::Update();
}
