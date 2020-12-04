#pragma once

/* 使用するデバイス設定 */
#define M5STACKBASIC 0 // M5Stack Basic
#define M5STACKCORE2 1 // M5Stack Core2
#define ATOMLITE     2 // ATOM Lite
#define ATOMMATRIX   3 // ATOM Matrix

#define DEVICE       0 // 使用するデバイスの数字を上から選んで記入してください

/* WiFi */
#define WIFI_SSID     "" // WiFiのSSID
#define WIFI_PASSWORD "" // WiFiのパスワード

/* LINE API */
#define LINE_HOST           "api.line.me"                // LINE Messaging APIのホスト名
#define LINE_BROADCAST_PATH "/v2/bot/message/broadcast"  // LINE Messaging APIのパス
#define LINE_PUSH_PATH      "/v2/bot/message/push"       // LINE Messaging APIのパス
#define LINE_TOKEN          "" // LINE Messaging APIのChannel access token
#define LINE_GROUP_ID       "" // LINE Group ID

/* SDカードのファイル名 */
#define FONT_PATH             "/fonts/genshin-regular-20"  // フォント名(.vlwは省略)

#define SELECT_SOUND_PATH     "/sounds/select.mp3"         // 選択時の音声ファイル
#define SUCCESS_SOUND_PATH    "/sounds/success.mp3"        // 成功時の音声ファイル
#define FAILED_SOUND_PATH     "/sounds/failed.mp3"         // 失敗時の音声ファイル

#define LOGO_IMAGE_PATH       "/images/logo.jpg"           // ロゴ画像
#define LOADING_IMAGE_PATH    "/images/UI2/loading.jpg"    // ローディング画面の画像ファイル
#define CONNECTING_IMAGE_PATH "/images/UI2/connecting.jpg" // WiFi接続中画面の画像ファイル
#define SENDING_IMAGE_PATH    "/images/UI2/sending.jpg"    // 送信中画面の画像ファイル
#define SUCCESS_IMAGE_PATH    "/images/UI2/success.jpg"    // 送信完了画面の画像ファイル
#define FAILED_IMAGE_PATH     "/images/UI2/failed.jpg"     // 送信失敗画面の画像ファイル
