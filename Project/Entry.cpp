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
  SERIAL_PRINTF("Storage entry count : %d\n", Storage::GetEntryCount());

  WifiMgr::Init();
  BasilWebServer::Init();
  BasilWebServer::Start();
}

void loop(void)
{
  PhMgr::Update();
  NutrientsMgr::Update();
}
