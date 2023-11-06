#include "src/WebServerImpl.h"
#include <WiFi.h>

AsyncWebServer server(80);

inline String urlToRegex(const String &url)
{
	String result = url;
	result.replace("/", "\\/");
	return "^" + result + "(\\?.*)?$";
}

void setup()
{
	WiFi.softAP("ESP32-Access-Point");

	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(200, "text/plain", "Hello, world"); });

	server.on(urlToRegex("/test").c_str(), HTTP_GET, [](AsyncWebServerRequest *request)
			  { request->send(200, "text/plain", "GET"); });

	server.on(
		urlToRegex("/test").c_str(), HTTP_POST, [](AsyncWebServerRequest *request)
		{ request->send(200, "text/plain", "POST"); },
		nullptr, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {});

	server.on(
		urlToRegex("/test").c_str(), HTTP_PUT, [](AsyncWebServerRequest *request)
		{ request->send(200, "text/plain", "PUT"); },
		nullptr, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {});

	server.begin();
}

void loop() {}