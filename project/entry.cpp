#include <arduino.h>
#include "config.h"
#include "serial.h"
#include "storage.h"
#include "WifiMgr.h"
#include "WebServer.h"

void setup()
{
  SERIAL_INIT(SERIAL_BAUD_RATE);
  Storage::Init();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);

  WifiMgr::SetupWifi();
  WifiMgr::ConnectWifi();

  WebServer::Setup();
}

void loop(void)
{
  PhMgr::Update();
  NutrientsMgr::Update();
  WebServer::Update();
}