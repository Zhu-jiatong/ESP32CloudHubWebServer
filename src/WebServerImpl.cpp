#include "WebServerImpl.h"

WebServer::WebServer(uint16_t port) : _server(port)
{
	_credentialManager.open("/sd/credential.db");

	// authentication handlers
	_server.on("/signin", HTTP_POST, signInResponse, nullptr, signInBody);
	_server.on("/signup", HTTP_POST, signUpResponse, nullptr, signUpBody);
	_server.on("/signout", HTTP_GET, signOut);

	// file handlers
	_server.on(URL("/file").c_str(), HTTP_GET, getFile);
	_server.on(URL("/file").c_str(), HTTP_POST, uploadFileResponse, uploadFileBody, createDirectoryBody);
	_server.on(URL("/file").c_str(), HTTP_PUT, renameFileResponse, nullptr, renameFileBody);
	_server.on(URL("/file").c_str(), HTTP_DELETE, deleteFileResponse, nullptr, deleteFileBody);
	_server.on(URL("/file").c_str(), HTTP_PATCH, shareFileResponse, nullptr, shareFileBody);
}

void WebServer::begin()
{
	_server.begin();
}

String WebServer::getContentType(const String &filename) const
{
	if (filename.endsWith(".htm") || filename.endsWith(".html"))
		return "text/html";
	else if (filename.endsWith(".css"))
		return "text/css";
	else if (filename.endsWith(".js"))
		return "application/javascript";
	else if (filename.endsWith(".png"))
		return "image/png";
	else if (filename.endsWith(".gif"))
		return "image/gif";
	else if (filename.endsWith(".jpg") || filename.endsWith(".jpeg"))
		return "image/jpeg";
	else if (filename.endsWith(".ico"))
		return "image/x-icon";
	else if (filename.endsWith(".pdf"))
		return "application/x-pdf";
	else if (filename.endsWith(".zip"))
		return "application/x-zip";
	else if (filename.endsWith(".gz"))
		return "application/x-gzip";
	return "text/plain";
}

String WebServer::getSessionId(AsyncWebServerRequest *request) const
{
	const String &cookieString = request->getHeader("Cookie")->value();
	int sessionIndex = cookieString.indexOf("session=");

	if (sessionIndex == -1)
		throw std::runtime_error("No session cookie found");

	sessionIndex += 8;
	int sessionEndIndex = cookieString.indexOf(";", sessionIndex);
	if (sessionEndIndex == -1)
		sessionEndIndex = cookieString.length();

	return cookieString.substring(sessionIndex, sessionEndIndex);
}

String WebServer::getUsername(AsyncWebServerRequest *request) const
{
	String sessionId = getSessionId(request);
}

String WebServer::URL(const String &url) const
{
	String result = url;
	result.replace("/", "\\/");
	return "^" + result + "(\\?.*)?$";
}