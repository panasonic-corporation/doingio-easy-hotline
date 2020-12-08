#include "Config.h"

#if DEVICE == M5STACKBASIC
#include <M5Stack.h>
#elif DEVICE == M5STACKCORE2
#include <M5Core2.h>
#elif DEVICE == ATOMLITE || DEVICE == ATOMMATRIX || DEVICE == ATOMECHO
#include <M5Atom.h>
#endif

#if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2 || DEVICE == ATOMECHO
#include "SoundPlayer.h"
#endif

#if USE_BLE == true
#include "BLEController.h"
BLEController* ble_controller = new BLEController();
#endif

#include <WiFi.h>
#include "UIController.h"
#include "LineApiClient.h"

const char* message_item[3] = {"今から出かけます", "今帰ったよ！", "緊急事態です！"}; // 定型文リスト

// WiFi接続
void connectWifi() {
    UIController::drawConnectingWifi();
    if ((WiFi.status() != WL_CONNECTED)) {
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        Serial.print("Connecting");
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print('.');
            delay(500);
        }
        Serial.println();
        Serial.printf("Connected, IP address : ");
        Serial.println(WiFi.localIP());
    }
}

// LINEへ投稿
bool sendLineMessage(String msg) {
  Serial.printf("Send : %s\n", msg.c_str());
  // 送信中画面表示
  UIController::drawSendingMessage();
  delay(200);
  //return LineApiClient::sendGroupMessage(msg);
  return LineApiClient::sendBroadcastMessage(msg);
}

// 選択時の動作
void onPushItem(int idx) {

    // 選択時に反転表示
    UIController::drawSelectedItem(idx, message_item[idx]);
    // 選択時の音を再生
    #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
      SoundPlayer::playMP3(SELECT_SOUND_PATH);
    #endif
    #if DEVICE == ATOMECHO
      SoundPlayer::playWAV();
    #endif


    // WiFi接続
    connectWifi();

    // LINEにメッセージ送信
    if (sendLineMessage(message_item[idx])) {
      // 送信成功画面表示
      UIController::drawStatusScreen(true);
      // 送信成功時の音を再生
      #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
        SoundPlayer::playMP3(SUCCESS_SOUND_PATH);
      #endif
    } else {
      // 送信失敗画面表示
      UIController::drawStatusScreen(false);
      // 送信成功時の音を再生
      #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
        SoundPlayer::playMP3(FAILED_SOUND_PATH);
      #endif
    }
    WiFi.disconnect();

    #if USE_BLE == true
      Serial.println("init ble");
      ble_controller->init();
      Serial.println("start advertise");
      ble_controller->startAdvertise(message_item[0]);
      delay(5000);
      Serial.println("stop advertise");
      ble_controller->stopAdvertise();
      Serial.println("deinit ble");
      ble_controller->deinit();
    #endif
    // メイン画面表示
    UIController::drawMainScreen(message_item);
}

void setup() {
  #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
    M5.begin();
  #elif DEVICE == ATOMLITE || DEVICE == ATOMMATRIX || DEVICE == ATOMECHO
    M5.begin(true, false, true);
    delay(50);
    M5.dis.setBrightness(70);
  #endif

  #if DEVICE == M5STACKBASIC
    M5.Power.begin();
  #elif DEVICE == M5STACKCORE2
    M5.Axp.SetSpkEnable(true);
  #endif

  #if DEVICE == M5STACKBASIC || DEVICE == M5STACKCORE2
    M5.Lcd.clear();
    M5.Lcd.setTextWrap(true, true);
    M5.Lcd.setRotation(2);

    // ロゴ表示
    M5.Lcd.drawJpgFile(SD, LOGO_IMAGE_PATH);
    delay(1000);
  #endif

  // Loading画面表示
  UIController::drawLoading();

  // メイン画面表示
  UIController::drawMainScreen(message_item);
}

void loop() {
#if DEVICE != M5STACKCORE2
  M5.update();
#endif

#if DEVICE == M5STACKBASIC
  if (M5.BtnC.wasPressed()) {
    onPushItem(0);
  }
  if (M5.BtnB.wasPressed()) {
    onPushItem(1);
  }
  if (M5.BtnA.wasPressed()) {
    onPushItem(2);
  }
#endif

#if DEVICE == M5STACKCORE2
  TouchPoint_t pos = M5.Touch.getPressPoint();
  if (pos.x > 0 && pos.y > 0) {
    if (pos.x > 2 * (320 / 3)) {
      onPushItem(0);
    } else if (pos.x > 320 / 3) {
      onPushItem(1);
    } else {
      onPushItem(2);
    }
  }
#endif

#if DEVICE == ATOMLITE || DEVICE == ATOMMATRIX || DEVICE == ATOMECHO
  UIController::drawMainScreen(message_item);
  if (M5.Btn.wasPressed()) {
    onPushItem(0);
  }
#endif

  delay(10);
}
