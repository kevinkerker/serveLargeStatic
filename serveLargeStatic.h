#ifndef A21B2A88_DCB4_459A_89A0_94CF0A5AED33
#define A21B2A88_DCB4_459A_89A0_94CF0A5AED33

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <SD.h>

#include <vector>

extern std::map<String, String> active_file_transfers;

class serveLargeStaticFolder {
 public:
  serveLargeStaticFolder(AsyncWebServer& Server, fs::FS& fs, char* path, char* cache_control);

  mutable FS __fs;
  AsyncWebServer __asyncWebServer;
  char* __path;
  char* __cache_control;
  bool downloadInProgress = false;
};

size_t load_data(File f, uint8_t* buffer, size_t maxLen, size_t index);
void init_slsf(char* uri);

#endif /* A21B2A88_DCB4_459A_89A0_94CF0A5AED33 */
