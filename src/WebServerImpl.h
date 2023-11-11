#if !defined(_WebServerImpl_h)
#define _WebServerImpl_h

#include <ESPAsyncWebServer.h>
#include <CredentialManager.h>
#include <SessionManager.h>

class WebServer
{
public:
	WebServer(uint16_t port = 80);

	void begin();

	// authentication handlers
	ArBodyHandlerFunction signInBody;
	ArBodyHandlerFunction signUpBody;
	ArRequestHandlerFunction signOut;
	ArRequestHandlerFunction signInResponse;
	ArRequestHandlerFunction signUpResponse;

	// file handlers
	ArRequestHandlerFunction getFile;

	ArUploadHandlerFunction uploadFileBody;
	ArRequestHandlerFunction uploadFileResponse;
	ArBodyHandlerFunction createDirectoryBody;

	ArBodyHandlerFunction renameFileBody;
	ArRequestHandlerFunction renameFileResponse;

	ArBodyHandlerFunction deleteFileBody;
	ArRequestHandlerFunction deleteFileResponse;

	ArBodyHandlerFunction shareFileBody;
	ArRequestHandlerFunction shareFileResponse;

	inline String URL(const String &url) const;

private:
	AsyncWebServer _server;
	CredentialManager _credentialManager;

	String getContentType(const String &filename) const;
	String getSessionId(AsyncWebServerRequest *request) const;
	String getUsername(AsyncWebServerRequest *request) const;
};

#endif // _WebServerImpl_h
