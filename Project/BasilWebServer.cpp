#include "BasilWebServer.h"

#include <arduino.h>
#include <stdio.h>

#include "Serial.h"
#include "NetworkInclude.h"
#include "WebUI.h"
#include "NutrientsMgr.h"
#include "PhMgr.h"

WebServer server(80);

void BasilWebServer::HandleRoot()
{
  digitalWrite(LED, 1);
  server.send(200, "text/html", WebUI::GetPageUI());
  digitalWrite(LED, 0);
}

void BasilWebServer::HandleNotFound()
{
  digitalWrite(LED, 1);
  server.send(404, "text/plain", "WUT?");
  digitalWrite(LED, 0);
}

void BasilWebServer::LowerPh()
{
  PhMgr::RunStepPhDown();
}

void BasilWebServer::RaisePh()
{
  PhMgr::RunStepPhUp();
}

void BasilWebServer::SetTargetPh()
{
  PhMgr::SetTarget(atof(server.arg(0).c_str()));
}

void BasilWebServer::SetTolerancePh()
{
  PhMgr::SetTolerance(atof(server.arg(0).c_str()));
}

void BasilWebServer::SetStepPh()
{
  PhMgr::SetStep(atoi(server.arg(0).c_str()));
}

void BasilWebServer::SetAdjustCooldownPh()
{
  PhMgr::SetAdjustCooldown(atoi(server.arg(0).c_str()));
}

void BasilWebServer::SetTestCooldownPh()
{
  PhMgr::SetTestCooldown(atoi(server.arg(0).c_str()));
}

void BasilWebServer::RaiseNutrients()
{
  NutrientsMgr::RunStepNutrientsUp();
}

void BasilWebServer::SetTargetNutrients()
{
  NutrientsMgr::SetTarget(atof(server.arg(0).c_str()));
}

void BasilWebServer::SetToleranceNutrients()
{
  NutrientsMgr::SetTolerance(atof(server.arg(0).c_str()));
}

void BasilWebServer::SetStepNutrients()
{
  NutrientsMgr::SetStep(atoi(server.arg(0).c_str()));
}

void BasilWebServer::SetAdjustCooldownNutrients()
{
  NutrientsMgr::SetAdjustCooldown(atoi(server.arg(0).c_str()));
}

void BasilWebServer::SetTestCooldownNutrients()
{
  NutrientsMgr::SetTestCooldown(atoi(server.arg(0).c_str()));
}

void BasilWebServer::Setup()
{
  server.on("/",                          HandleRoot);
  server.on("/lower-ph",                  LowerPh);
  server.on("/raise-ph",                  RaisePh);
  server.on("/target-ph",                 SetTargetPh);
  server.on("/tolerance-ph",              SetTolerancePh);
  server.on("/step-ph",                   SetStepPh);
  server.on("/adjust-cooldown-ph",        SetAdjustCooldownPh);
  server.on("/test-cooldown-ph",          SetTestCooldownPh);
  server.on("/raise-nutrients",           RaiseNutrients);
  server.on("/target-nutrients",          SetTargetNutrients);
  server.on("/tolerance-nutrients",       SetToleranceNutrients);
  server.on("/step-nutrients",            SetStepNutrients);
  server.on("/adjust-cooldown-nutrients", SetAdjustCooldownNutrients);
  server.on("/test-cooldown-nutrients",   SetTestCooldownNutrients);

  server.onNotFound(HandleNotFound);

  server.begin();
  SERIAL_PRINTLN("HTTP server started");
}

void BasilWebServer::Update()
{
  server.handleClient();
  //MDNS.update();
}