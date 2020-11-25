#pragma once

#define M5STACKBASIC 0 // M5StackBasic
#define M5STACKCORE2 1 // M5StackCore2
#define ATOMLITE     2 // AtomLite
#define ATOMMATRIX   3 // AtomMatrix

#define DEVICE       0 // 使用するデバイスの数字を上から選んで記入してください

#define WIFI_SSID     "" // WiFiのSSID
#define WIFI_PASSWORD "" // WiFiのパスワード

#define LINE_HOST             "api.line.me"                // LINE Messaging APIのホスト名
#define LINE_BROADCAST_PATH   "/v2/bot/message/broadcast"  // LINE Messaging APIのパス
#define LINE_TOKEN            ""                           // LINE Messaging APIのChannel access token

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
