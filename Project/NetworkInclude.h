#ifndef NETWORKINCLUDE_HEADER
#define NETWORKINCLUDE_HEADER

#ifdef ESP32

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
//#include <ESPmDNS.h>
//#include <WiFiClient.h>

#else

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
//#include <ESP8266mDNS.h>
//#include <WiFiClient.h>

#define WebServer ESP8266WebServer

#endif

#endif