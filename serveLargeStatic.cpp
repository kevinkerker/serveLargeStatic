#include "serveLargeStatic.h"

#include <FS.h>

bool downloadInProgress = false;

size_t load_data(File f, uint8_t* buffer, size_t maxLen, size_t index) {
  if (f.available()) {
    // infolog("Write Chunked Data\n");
    return f.read(buffer, maxLen);
  } else {
    downloadInProgress = false;
    return 0;
  }
}

void serveLargeStatic(AsyncWebServer& Server, const char* uri, fs::FS& fs, const char* path,
                      const char* cache_control) {
  Server.on(uri, HTTP_GET, [](AsyncWebServerRequest* request) {
    // infolog("Log requested!\n");
    if (downloadInProgress) request->send(429);  // Too Many Requests;
    downloadInProgress = true;
    File file = fs.open((path + "/" + request->pathArg(0).c_str()).c_str(), FILE_READ);
    if (file) {
      AsyncWebServerResponse* response = request->beginChunkedResponse(
          "text/plain", [file](uint8_t* buffer, size_t maxLen, size_t index) -> size_t {
            return load_data(file, buffer, 512, index);
          });
      response->addHeader("size", String(file.size()));
      request->send(response);
    } else {
      request->send(400);  // Bad Request;
    }
  });
}