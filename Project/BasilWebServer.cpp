#include "BasilWebServer.h"

#include <arduino.h>
#include <stdio.h>

#include "Serial.h"
#include "NetworkInclude.h"
#include "WebUI.h"
#include "Storage.h"
#include "WifiMgr.h"
#include "NutrientsMgr.h"
#include "PhMgr.h"
#include "HTML.h"

AsyncWebServer server(80);
static char commonBuffer[4096];

void HandleRoot(AsyncWebServerRequest* request)
{
  digitalWrite(LED, 1);
  request->send(200, "text/html", HTML::IndexPage);
  digitalWrite(LED, 0);
}

void HandlePanel(AsyncWebServerRequest* request) {
  snprintf(commonBuffer, sizeof(commonBuffer), HTML::PanelPage,
    PhMgr::GetCurrentPh(),
    STATUS_STRING[PhMgr::GetStatus()],
    PhMgr::GetTarget(),
    PhMgr::GetTolerance(),
    PhMgr::GetStep(),
    PhMgr::GetAdjustCooldown(),
    PhMgr::GetTestCooldown(),
    NutrientsMgr::GetCurrentNutrients(),
    STATUS_STRING[NutrientsMgr::GetStatus()],
    NutrientsMgr::GetTarget(),
    NutrientsMgr::GetTolerance(),
    NutrientsMgr::GetStep(),
    NutrientsMgr::GetAdjustCooldown(),
    NutrientsMgr::GetTestCooldown()
  );

  request->send(200, "text/html", commonBuffer);
}

void HandleSettings(AsyncWebServerRequest* request) {
  WifiMgr::WifiCredentials apCredentials = WifiMgr::GetAPCredentials();

  snprintf(commonBuffer, sizeof(commonBuffer), HTML::SettingsPage,
    WifiMgr::IsConnected() ? WifiMgr::GetConnectedWifiSSID().c_str() : "NONE",
    apCredentials.ssid,
    apCredentials.ssid,
    apCredentials.password
  );

  request->send(200, "text/html", commonBuffer);
}

void HandleStylesheet(AsyncWebServerRequest* request) {
  request->send(200, "text/css", HTML::Stylesheet);
}

void LowerPh(AsyncWebServerRequest* request)
{
  request->send(200, "text/plain", "Ok");
  PhMgr::RunStepPhDown();
}

void RaisePh(AsyncWebServerRequest* request)
{
  request->send(200, "text/plain", "Ok");
  PhMgr::RunStepPhUp();
}

void SetTargetPh(AsyncWebServerRequest* request)
{
  if (request->params() < 1) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* parameter = request->getParam(0);

  PhMgr::SetTarget(atof(parameter->value().c_str()));
}

void SetTolerancePh(AsyncWebServerRequest* request)
{
  if (request->params() < 1) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* parameter = request->getParam(0);

  PhMgr::SetTolerance(atof(parameter->value().c_str()));
}

void SetStepPh(AsyncWebServerRequest* request)
{
  if (request->params() < 1) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* parameter = request->getParam(0);

  PhMgr::SetStep(atoi(parameter->value().c_str()));
}

void SetAdjustCooldownPh(AsyncWebServerRequest* request)
{
  if (request->params() < 1) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* parameter = request->getParam(0);

  PhMgr::SetAdjustCooldown(atoi(parameter->value().c_str()));
}

void SetTestCooldownPh(AsyncWebServerRequest* request)
{
  if (request->params() < 1) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* parameter = request->getParam(0);

  PhMgr::SetTestCooldown(atoi(parameter->value().c_str()));
}

void RaiseNutrients(AsyncWebServerRequest* request)
{
  request->send(200, "text/plain", "Ok");
  NutrientsMgr::RunStepNutrientsUp();
}

void SetTargetNutrients(AsyncWebServerRequest* request)
{
  if (request->params() < 1) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* parameter = request->getParam(0);

  NutrientsMgr::SetTarget(atof(parameter->value().c_str()));
}

void SetToleranceNutrients(AsyncWebServerRequest* request)
{
  if (request->params() < 1) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* parameter = request->getParam(0);

  NutrientsMgr::SetTolerance(atof(parameter->value().c_str()));
}

void SetStepNutrients(AsyncWebServerRequest* request)
{
  if (request->params() < 1) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* parameter = request->getParam(0);

  NutrientsMgr::SetStep(atoi(parameter->value().c_str()));
}

void SetAdjustCooldownNutrients(AsyncWebServerRequest* request)
{
  if (request->params() < 1) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* parameter = request->getParam(0);

  NutrientsMgr::SetAdjustCooldown(atoi(parameter->value().c_str()));
}

void SetTestCooldownNutrients(AsyncWebServerRequest* request)
{
  if (request->params() < 1) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* parameter = request->getParam(0);

  NutrientsMgr::SetTestCooldown(atoi(parameter->value().c_str()));
}

void ConnectWifi(AsyncWebServerRequest* request) {
  if (request->params() < 2) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* ssid = request->getParam(0);
  AsyncWebParameter* password = request->getParam(1);

  if (ssid->value().length() < 2 || ssid->value().length() > 32) {
    SERIAL_PRINTLN("Can't connect to WIFI : SSID to short or too long (2-32)");
    return;
  }
  if (password->value().length() < 8 || password->value().length() > 63){
    SERIAL_PRINTLN("Can't connect to WIFI : Password to short or too long (8-63)");
    return;
  }

  WifiMgr::WifiCredentials credentials{ 0 };
  memcpy(credentials.ssid, ssid->value().c_str(), ssid->value().length() + 1);
  memcpy(credentials.password, password->value().c_str(), password->value().length() + 1);

  WifiMgr::Connect(credentials);
}

void UpdateAPSettings(AsyncWebServerRequest* request) {
  if (request->params() < 2) {
    SERIAL_PRINTF("%s failed. bad number of argument (%d)\n", request->url(), request->params());
    request->send(400, "text/plain", "Bad request.");
    return;
  } else {
    request->send(200, "text/plain", "Ok");
  }

  AsyncWebParameter* ssid = request->getParam(0);
  AsyncWebParameter* password = request->getParam(1);

  SERIAL_PRINTF("Updating AP settings.\nSSID : %s\nPASSWORD : %s\n", ssid->value().c_str(), password->value().c_str());

  if (ssid->value().length() < 2 || ssid->value().length() > 32) {
    SERIAL_PRINTLN("SSID to short or too long (2-32)");
    return;
  }
  if (password->value().length() < 8 || password->value().length() > 63){
    SERIAL_PRINTLN("Password to short or too long (8-63)");
    return;
  }

  WifiMgr::WifiCredentials credentials{ 0 };
  memcpy(credentials.ssid, ssid->value().c_str(), ssid->value().length() + 1);
  memcpy(credentials.password, password->value().c_str(), password->value().length() + 1);
  Storage::StorageEntry credentialsStorageEntry = Storage::CreateEntry(ESP_AP_STORAGE_ENTRY_NAME, sizeof(WifiMgr::WifiCredentials));
  Storage::Write(credentialsStorageEntry, (char*)&credentials, sizeof(WifiMgr::WifiCredentials));
}

void BasilWebServer::Init()
{
  server.on("/",                          HTTP_GET,  HandleRoot);
  server.on("/panel.html",                HTTP_GET,  HandlePanel);
  server.on("/settings.html",             HTTP_GET,  HandleSettings);
  server.on("/stylesheet.css",            HTTP_GET,  HandleStylesheet);

  server.on("/lower-ph",                  HTTP_POST, LowerPh);
  server.on("/raise-ph",                  HTTP_POST, RaisePh);
  server.on("/target-ph",                 HTTP_POST, SetTargetPh);
  server.on("/tolerance-ph",              HTTP_POST, SetTolerancePh);
  server.on("/step-ph",                   HTTP_POST, SetStepPh);
  server.on("/adjust-cooldown-ph",        HTTP_POST, SetAdjustCooldownPh);
  server.on("/test-cooldown-ph",          HTTP_POST, SetTestCooldownPh);
  server.on("/raise-nutrients",           HTTP_POST, RaiseNutrients);
  server.on("/target-nutrients",          HTTP_POST, SetTargetNutrients);
  server.on("/tolerance-nutrients",       HTTP_POST, SetToleranceNutrients);
  server.on("/step-nutrients",            HTTP_POST, SetStepNutrients);
  server.on("/adjust-cooldown-nutrients", HTTP_POST, SetAdjustCooldownNutrients);
  server.on("/test-cooldown-nutrients",   HTTP_POST, SetTestCooldownNutrients);
  server.on("/connect-wifi",              HTTP_POST, ConnectWifi);
  server.on("/update-ap-settings",        HTTP_POST, UpdateAPSettings);
}

void BasilWebServer::Start()
{
  server.begin();
  SERIAL_PRINTLN("HTTP server started");
}