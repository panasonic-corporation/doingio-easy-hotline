#include "Config.h"
#include "UIController.h"

#if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
const int item_height = (M5.Lcd.height() - 2) / 3; // 1ブロックの高さ
#endif

// メイン画面表示
void UIController::drawMainScreen(const char *message_item[]) {
  #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
    M5.Lcd.loadFont(FONT_PATH, SD);
    M5.Lcd.fillRect(0, 0, M5.Lcd.width(), M5.Lcd.height(), WHITE);
    M5.Lcd.drawLine(0, item_height, M5.Lcd.width(), item_height, BLACK);
    M5.Lcd.drawLine(0, item_height * 2 + 1, M5.Lcd.width(), item_height * 2 + 1, BLACK);
    M5.Lcd.setTextColor(BLACK, WHITE);
    for (int i = 0; i < 3; i++) {
      M5.Lcd.drawString(message_item[i], 10, i * M5.Lcd.height() / 3 + 45);
    }
  #elif DEVICE == ATOMLITE || DEVICE == ATOMECHO
    M5.dis.drawpix(0, 0xffffff);
  #elif DEVICE == ATOMMATRIX
    int dots[] = {1, 1, 1, 1, 1,
                  1, 2, 2, 2, 1,
                  1, 2, 3, 2, 1,
                  1, 2, 2, 2, 1,
                  1, 1, 1, 1, 1};
    for (int i = 0; i < 25; i++) {
      if (dots[i] == 1) {
        M5.dis.drawpix(i, 0x333333);
      } else if (dots[i] == 2) {
        M5.dis.drawpix(i, 0x777777);
      } else {
        M5.dis.drawpix(i, 0xffffff);
      }
    }

  #endif
}

// 選択時のアイテム表示
void UIController::drawSelectedItem(int idx, const char *message) {
  #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
    uint16_t bg_color;
    if (idx == 0) {
      bg_color = BLUE;
    } else if (idx == 1) {
      bg_color = DARKGREEN;
    } else {
      bg_color = RED;
    }
    int border_width = 5;
    M5.Lcd.setTextColor(WHITE, bg_color);
    M5.Lcd.fillRect(0, item_height * idx + idx, M5.Lcd.width(), item_height, bg_color);
    M5.Lcd.drawString(message, 10, idx * M5.Lcd.height() / 3 + 45);
    M5.Lcd.unloadFont();
  #endif
}

// ステータス画面表示
void UIController::drawStatusScreen(bool success) {
  #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
    if (success) {
      M5.Lcd.drawJpgFile(SD, SUCCESS_IMAGE_PATH);
    } else {
      M5.Lcd.drawJpgFile(SD, FAILED_IMAGE_PATH);
    }
  #elif DEVICE == ATOMLITE || DEVICE == ATOMECHO
    if (success) {
      M5.dis.drawpix(0, 0x0044ff);
    } else {
      M5.dis.drawpix(0, 0x00ff00);
    }
  #elif DEVICE == ATOMMATRIX
    if (success) {
      int dots[] = {0, 1, 1, 1, 0,
                    1, 0, 0, 0, 1,
                    1, 0, 0, 0, 1,
                    1, 0, 0, 0, 1,
                    0, 1, 1, 1, 0};
      for (int i = 0; i < 25; i++) {
        if (dots[i] > 0) {
          M5.dis.drawpix(i, 0x0044ff);
        } else {
          M5.dis.drawpix(i, 0x000000);
        }
      }
    } else {
      int dots[] = {1, 0, 0, 0, 1,
                    0, 1, 0, 1, 0,
                    0, 0, 1, 0, 0,
                    0, 1, 0, 1, 0,
                    1, 0, 0, 0, 1};
      for (int i = 0; i < 25; i++) {
        if (dots[i] > 0) {
          M5.dis.drawpix(i, 0x00ff00);
        } else {
          M5.dis.drawpix(i, 0x000000);
        }
      }
    }
  #endif
  delay(500);
}

// WiFi接続中の表示
void UIController::drawConnectingWifi() {
  #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
    M5.Lcd.drawJpgFile(SD, CONNECTING_IMAGE_PATH);
  #elif DEVICE == ATOMLITE || DEVICE == ATOMECHO
    M5.dis.drawpix(0, 0xffff00);
  #elif DEVICE == ATOMMATRIX
    int dots[] = {0, 1, 1, 1, 0,
                  1, 0, 1, 0, 1,
                  0, 1, 0, 1, 0,
                  0, 0, 0, 0, 0,
                  0, 0, 1, 0, 0};
    for (int i = 0; i < sizeof(dots)/sizeof(dots[0]); i++) {
      if (dots[i] > 0) {
        M5.dis.drawpix(i, 0xffff00);
      }
    }

  #endif
}

// 送信中の表示
void UIController::drawSendingMessage() {
  #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
    M5.Lcd.drawJpgFile(SD, SENDING_IMAGE_PATH);
  #elif DEVICE == ATOMLITE || DEVICE == ATOMECHO
    M5.dis.drawpix(0, 0xff00ff);
  #elif DEVICE == ATOMMATRIX
    int dots[] = {0, 1, 1, 1, 1,
                  0, 0, 0, 1, 1,
                  0, 0, 1, 0, 1,
                  0, 1, 0, 0, 1,
                  1, 0, 0, 0, 0};
    for (int i = 0; i < 25; i++) {
      if (dots[i] > 0) {
        M5.dis.drawpix(i, 0xff00ff);
      } else {
        M5.dis.drawpix(i, 0x000000);
      }
    }
  #endif
}

// ローディング中の表示
void UIController::drawLoading() {
  #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
    M5.Lcd.drawJpgFile(SD, LOADING_IMAGE_PATH);
  #endif
}