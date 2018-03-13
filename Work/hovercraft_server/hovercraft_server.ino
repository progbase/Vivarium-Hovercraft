#include <ESP8266WiFi.h>
#include "FS.h"
#include <WiFiClient.h>
#include <TimeLib.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include "hovercraft_server_lib.h"
#include <Hash.h>

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  SPIFFS.begin(); // Not really needed, checked inside library and started if needed
  ESPHTTPServer.begin(&SPIFFS);
}

void loop() {
  // put your main code here, to run repeatedly:
  // DO NOT REMOVE. Attend OTA update from Arduino IDE
  ESPHTTPServer.handle();
}
