#include "hovercraft_server_lib.h"
#include <StreamString.h>

String APssid = "ESP";
//String APpassword = "12345678";
String DeviceName = "Hovercraft";

AsyncFSWebServer ESPHTTPServer(80);
AsyncFSWebServer::AsyncFSWebServer(uint16_t port) : AsyncWebServer(port) {}

void AsyncFSWebServer::begin(FS* fs) {
	_fs = fs;
	Serial.begin(4800);
	Serial.println("BEGIN");
  
	if (!_fs) // If SPIFFS is not started
		_fs->begin();

	//WIFI INIT

	/*NTP.begin(_config.ntpServerName, _config.timezone / 10, _config.daylight);
	NTP.setInterval(15, _config.updateNTPTimeEvery * 60);*/

	WiFi.hostname(DeviceName);

	configureWifiAP(); // Set AP mode if AP button was pressed

	//_secondTk.attach(1.0f, &AsyncFSWebServer::s_secondTick, static_cast<void*>(this)); // Task to run periodic things every second

	AsyncWebServer::begin();
	serverInit(); // Configure and start Web server

}

void AsyncFSWebServer::configureWifiAP() {

	WiFi.mode(WIFI_AP);
	String APname = APssid + (String)ESP.getChipId();
	WiFi.softAP(APname.c_str());

}

String getContentType(String filename, AsyncWebServerRequest *request) {
	if (request->hasArg("download")) return "application/octet-stream";
	else if (filename.endsWith(".htm")) return "text/html";
	else if (filename.endsWith(".html")) return "text/html";
	else if (filename.endsWith(".css")) return "text/css";
	else if (filename.endsWith(".js")) return "application/javascript";
	else if (filename.endsWith(".json")) return "application/json";
	else if (filename.endsWith(".png")) return "image/png";
	else if (filename.endsWith(".gif")) return "image/gif";
	else if (filename.endsWith(".jpg")) return "image/jpeg";
	else if (filename.endsWith(".ico")) return "image/x-icon";
	else if (filename.endsWith(".xml")) return "text/xml";
	else if (filename.endsWith(".pdf")) return "application/x-pdf";
	else if (filename.endsWith(".zip")) return "application/x-zip";
	else if (filename.endsWith(".gz")) return "application/x-gzip";
	return "text/plain";
}

void AsyncFSWebServer::logRequest(String msg, AsyncWebServerRequest *request) {
	Serial.println("LogRequest");
	Serial.println("================================");
	Serial.println(msg);
	for (uint8_t i = 0; i < request->args(); i++) {
		Serial.println(request->arg(i).c_str());
		Serial.println(request->argName(i).c_str());
	}
}
void executeCommand(String prm){
  Serial.println("#" + prm + "#");
}

void AsyncFSWebServer::processRequest(AsyncWebServerRequest *request) {
	uint8_t argsCount = request->args();
  uint8_t i = 0;
  Serial.println(argsCount);
	if (argsCount == 1)
	{
  Serial.println(request->argName(i).c_str());
    if (strstr(request->argName(i).c_str(), "direction") != NULL)
    {
     
			executeCommand(request->arg(i).c_str());
    }
		else
    {
     
			//processSpeed(request->arg(i).c_str());
    }
	}
}



bool AsyncFSWebServer::handleFileRead(String path, AsyncWebServerRequest *request) {
	if (path.endsWith("/"))
		path += "index.htm";
	String contentType = getContentType(path, request);
	String pathWithGz = path + ".gz";
	if (_fs->exists(pathWithGz) || _fs->exists(path)) {
		if (_fs->exists(pathWithGz)) {
			path += ".gz";
		}
		AsyncWebServerResponse *response = request->beginResponse(*_fs, path, contentType);
		if (path.endsWith(".gz"))
			response->addHeader("Content-Encoding", "gzip");
		request->send(response);

		return true;
	}
	return false;
}

void AsyncFSWebServer::serverInit() {
	on("/", [this](AsyncWebServerRequest *request) {
		if (!this->handleFileRead("/", request))
			request->send(404, "text/plain", "FileNotFound");
	});
	on("/index.htm", [this](AsyncWebServerRequest *request) {
		this->logRequest("index", request);
    this->processRequest(request);
		if (!this->handleFileRead("/index.htm", request))
			request->send(404, "text/plain", "FileNotFound");
	});
	on("/back.png", [this](AsyncWebServerRequest *request) {
		//this->logRequest("back", request);
		if (!this->handleFileRead("/back.png", request))
			request->send(404, "text/plain", "FileNotFound");
	});
	on("/forward.png", [this](AsyncWebServerRequest *request) {
		//this->logRequest("forward", request);
		if (!this->handleFileRead("/forward.png", request))
			request->send(404, "text/plain", "FileNotFound");
	});
	on("/left.png", [this](AsyncWebServerRequest *request) {
		//this->logRequest("left", request);
		if (!this->handleFileRead("/left.png", request))
			request->send(404, "text/plain", "FileNotFound");
	});
	on("/right.png", [this](AsyncWebServerRequest *request) {
		//this->logRequest("right", request);
		if (!this->handleFileRead("/right.png", request))
			request->send(404, "text/plain", "FileNotFound");
	});
	on("/rotate.png", [this](AsyncWebServerRequest *request) {
		//this->logRequest("rotate", request);
		if (!this->handleFileRead("/rotate.png", request))
			request->send(404, "text/plain", "FileNotFound");
	});
}


void AsyncFSWebServer::handle() {

}

