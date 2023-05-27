#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "WebUI.h"

namespace WebServer
{
  ESP8266WebServer server(80);

  void HandleRoot()
  {
    digitalWrite(LED, 1);
    server.send(200, "text/html", WebUI::GetPageUI());
    digitalWrite(LED, 0);
  }

  void HandleNotFound()
  {
    digitalWrite(LED, 1);
    server.send(404, "text/plain", "WUT?");
    digitalWrite(LED, 0);
  }

  void LowerPh()
  {
    PhMgr::RunStepPhDown();
  }

  void RaisePh()
  {
    PhMgr::RunStepPhUp();
  }

  void SetTargetPh()
  {
    PhMgr::SetTarget(atof(server.arg(0).c_str()));
  }

  void SetTolerancePh()
  {
    PhMgr::SetTolerance(atof(server.arg(0).c_str()));
  }

  void SetStepPh()
  {
    PhMgr::SetStep(atoi(server.arg(0).c_str()));
  }

  void SetAdjustCooldownPh()
  {
    PhMgr::SetAdjustCooldown(atoi(server.arg(0).c_str()));
  }

  void SetTestCooldownPh()
  {
    PhMgr::SetTestCooldown(atoi(server.arg(0).c_str()));
  }

  void RaiseNutrients()
  {
    NutrientsMgr::RunStepNutrientsUp();
  }

  void SetTargetNutrients()
  {
    NutrientsMgr::SetTarget(atof(server.arg(0).c_str()));
  }

  void SetToleranceNutrients()
  {
    NutrientsMgr::SetTolerance(atof(server.arg(0).c_str()));
  }

  void SetStepNutrients()
  {
    NutrientsMgr::SetStep(atoi(server.arg(0).c_str()));
  }

  void SetAdjustCooldownNutrients()
  {
    NutrientsMgr::SetAdjustCooldown(atoi(server.arg(0).c_str()));
  }

  void SetTestCooldownNutrients()
  {
    NutrientsMgr::SetTestCooldown(atoi(server.arg(0).c_str()));
  }

  void Setup(void)
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

  void Update()
  {
    server.handleClient();
    MDNS.update();
  }
}

