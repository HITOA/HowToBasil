#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "WebUI.h"

namespace WebServer
{
  ESP8266WebServer server(80);

  void handleRoot()
  {
    digitalWrite(LED, 1);
    server.send(200, "text/html", WebUI::getPageUI());
    digitalWrite(LED, 0);
  }

  void handleNotFound()
  {
    digitalWrite(LED, 1);
    server.send(404, "text/plain", "WUT?");
    digitalWrite(LED, 0);
  }

  void lowerPh()
  {
    PhMgr::runStepPhDown();
  }

  void raisePh()
  {
    PhMgr::runStepPhUp();
  }

  void setTargetPh()
  {
    PhMgr::setTarget(atof(server.arg(0).c_str()));
  }

  void setTolerancePh()
  {
    PhMgr::setTolerance(atof(server.arg(0).c_str()));
  }

  void setStepPh()
  {
    PhMgr::setStep(atoi(server.arg(0).c_str()));
  }

  void setAdjustCooldownPh()
  {
    PhMgr::setAdjustCooldown(atoi(server.arg(0).c_str()));
  }

  void setTestCooldownPh()
  {
    PhMgr::setTestCooldown(atoi(server.arg(0).c_str()));
  }

  void raiseNutrients()
  {
    NutrientsMgr::runStepNutrientsUp();
  }

  void setTargetNutrients()
  {
    NutrientsMgr::setTarget(atof(server.arg(0).c_str()));
  }

  void setToleranceNutrients()
  {
    NutrientsMgr::setTolerance(atof(server.arg(0).c_str()));
  }

  void setStepNutrients()
  {
    NutrientsMgr::setStep(atoi(server.arg(0).c_str()));
  }

  void setAdjustCooldownNutrients()
  {
    NutrientsMgr::setAdjustCooldown(atoi(server.arg(0).c_str()));
  }

  void setTestCooldownNutrients()
  {
    NutrientsMgr::setTestCooldown(atoi(server.arg(0).c_str()));
  }

  void setup(void)
  {
    server.on("/",                          handleRoot);
    server.on("/lower-ph",                  lowerPh);
    server.on("/raise-ph",                  raisePh);
    server.on("/target-ph",                 setTargetPh);
    server.on("/tolerance-ph",              setTolerancePh);
    server.on("/step-ph",                   setStepPh);
    server.on("/adjust-cooldown-ph",        setAdjustCooldownPh);
    server.on("/test-cooldown-ph",          setTestCooldownPh);
    server.on("/raise-nutrients",           raiseNutrients);
    server.on("/target-nutrients",          setTargetNutrients);
    server.on("/tolerance-nutrients",       setToleranceNutrients);
    server.on("/step-nutrients",            setStepNutrients);
    server.on("/adjust-cooldown-nutrients", setAdjustCooldownNutrients);
    server.on("/test-cooldown-nutrients",   setTestCooldownNutrients);

    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
  }

  void update()
  {
    server.handleClient();
    MDNS.update();
  }
}

