
#ifndef _FSWEBSERVERLIB_h
#define _FSWEBSERVERLIB_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define DBG_OUTPUT_PORT Serial

#ifndef RELEASE
#define DEBUGLOG(...) DBG_OUTPUT_PORT.printf(__VA_ARGS__)
#else
#define DEBUGLOG(...)
#endif


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>



enum Direction {
	NONE,
	STOP,
	FORWARD,
	RIGHT,
	BACK,
	LEFT,
	ROTATE
};

class AsyncFSWebServer : public AsyncWebServer {
public:
	AsyncFSWebServer(uint16_t port);
	void begin(FS* fs);
	void handle();
	const char* getHostName();
protected:
	FS* _fs;
	void configureWifiAP();
	void serverInit();
	bool handleFileRead(String path, AsyncWebServerRequest *request);
  void logRequest(String msg, AsyncWebServerRequest *request);
  void processRequest(AsyncWebServerRequest *request);
};
extern AsyncFSWebServer ESPHTTPServer;
#endif
