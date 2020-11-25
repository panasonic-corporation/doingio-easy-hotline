#pragma once

#if DEVICE == M5STACKBASIC
  #include <M5Stack.h>
#elif DEVICE == M5STACKCORE2
  #include <M5Core2.h>
#elif DEVICE == ATOMLITE || DEVICE == ATOMMATRIX
  #include <M5Atom.h>
#endif
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

class LineApiClient {
private:

public:
    static bool sendBroadcastMessage(String message);
};