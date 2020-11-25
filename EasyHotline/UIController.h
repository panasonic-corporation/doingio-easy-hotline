#pragma once

#if DEVICE == M5STACKBASIC
  #include <M5Stack.h>
#elif DEVICE == M5STACKCORE2
  #include <M5Core2.h>
#elif DEVICE == ATOMLITE || DEVICE == ATOMMATRIX
  #include <M5Atom.h>
#endif

class UIController {
private:

public:
    static void drawMainScreen(const char *message_item[]);
    static void drawSelectedItem(int idx, const char *message);
    static void drawStatusScreen(bool success);
    static void drawConnectingWifi();
    static void drawSendingMessage();
    static void drawLoading();
};