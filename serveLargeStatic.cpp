#include "serveLargeStatic.h"

std::map<String, String> active_file_transfers = {};

serveLargeStaticFolder::serveLargeStaticFolder(AsyncWebServer& Server, fs::FS& fs, char* path,
                                               char* cache_control)
    : __fs(fs), __path(path), __cache_control(cache_control), __asyncWebServer(Server) {
  // __fs = fs;
  // __asyncWebServer = Server;
  // __path = path;
  // __cache_control = cache_control;
}

size_t load_data(File f, uint8_t* buffer, size_t maxLen, size_t index) {
  if (f.available()) {
    // infolog("Write Chunked Data\n");
    return f.read(buffer, maxLen);
  } else {
    // downloadInProgress = false;
    return 0;
  }
}

void init_slsf(char* uri, serveLargeStaticFolder& folder) {
  folder.__asyncWebServer.on(uri, HTTP_GET, [folder](AsyncWebServerRequest* request) {
    // infolog("Log requested!\n");

    File file = folder.__fs.open(folder.__path, FILE_READ);
    std::map<String, String>::const_iterator pos = active_file_transfers.find(request->url());
    if (pos != active_file_transfers.end()) {
      active_file_transfers[request->url()] = request->host();
      AsyncWebServerResponse* response = request->beginChunkedResponse(
          "text/plain", [file](uint8_t* buffer, size_t maxLen, size_t index) -> size_t {
            return load_data(file, buffer, 512, index);
          });
      response->addHeader("size", String(file.size()));
      request->send(response);
      active_file_transfers.erase(request->url());
    } else {
      request->send(400);  // Bad Request;
    }
  });
}