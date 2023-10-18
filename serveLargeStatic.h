#ifndef A21B2A88_DCB4_459A_89A0_94CF0A5AED33
#define A21B2A88_DCB4_459A_89A0_94CF0A5AED33

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

void serveLargeStatic(AsyncWebServer& Server, const char* uri, fs::FS& fs, const char* path,
                      const char* cache_control);

#endif /* A21B2A88_DCB4_459A_89A0_94CF0A5AED33 */
