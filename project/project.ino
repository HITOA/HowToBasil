#include <EEPROM.h>

#include "WifiMgr.h"
#include "data.h"
#include "WebServer.h"

void setup(void)
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  Serial.begin(9600);
  Serial.println("");

  WifiMgr::setupWifi();
  WifiMgr::connectWifi();

  WebServer::setup();
}

void loop(void)
{
  PhMgr::update();
  NutrientsMgr::update();
  WebServer::update();
}