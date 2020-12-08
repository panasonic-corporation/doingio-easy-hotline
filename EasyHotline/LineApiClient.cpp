#include "Config.h"
#include "LineApiClient.h"
// GETリクエスト
/**
 * response_json : JSONレスポンス
 * url : URL
 * return :  1  成功
 *          -1 desirializeJson失敗
 *          -2 エラーレスポンス
 *          -3 WiFi接続失敗
 */
bool LineApiClient::sendBroadcastMessage(String message) {
    WiFiClientSecure client;
    HTTPClient http_client;
    http_client.begin(client, LINE_HOST, 443, LINE_BROADCAST_PATH, true);
    http_client.addHeader("Authorization", String("Bearer ") + String(LINE_TOKEN));
    http_client.addHeader("Content-Type", "application/json");
    Serial.print("has header : ");
    Serial.println(http_client.hasHeader("Content-Type"));
    Serial.print("header num : ");
    Serial.println(http_client.headers());
    for (int i = 0; i < http_client.headers(); i++) {
        Serial.print(http_client.headerName(i));
        Serial.print(" : ");
        Serial.println(http_client.header(i));
    }

    // リクエスト
    String payload = "{\"messages\":[{\"type\":\"text\",\"text\":\"" + message + "\"}]}";
    int http_code = http_client.POST(payload);
    Serial.println(http_code);
    if (http_code == 200) {
        // response取得
        String response = http_client.getString();
        Serial.println(response);
        http_client.end();
        return true;
    } else {
        // エラーレスポンス
        Serial.println("Error on http request");
        http_client.end();
        return false;
    }
}

#if defined(LINE_GROUP_ID)
bool LineApiClient::sendGroupMessage(String message) {
    WiFiClientSecure client;
    HTTPClient http_client;
    http_client.begin(client, LINE_HOST, 443, LINE_PUSH_PATH, true);
    http_client.addHeader("Authorization", String("Bearer ") + String(LINE_TOKEN));
    http_client.addHeader("Content-Type", "application/json");
    Serial.print("has header : ");
    Serial.println(http_client.hasHeader("Content-Type"));
    Serial.print("header num : ");
    Serial.println(http_client.headers());
    for (int i = 0; i < http_client.headers(); i++) {
        Serial.print(http_client.headerName(i));
        Serial.print(" : ");
        Serial.println(http_client.header(i));
    }

    // リクエスト
    String payload = "{\"to\":\"" LINE_GROUP_ID "\",\"messages\":[{\"type\":\"text\",\"text\":\"" + message + "\"}]}";
    int http_code = http_client.POST(payload);
    Serial.println(http_code);
    if (http_code == 200) {
        // response取得
        String response = http_client.getString();
        Serial.println(response);
        http_client.end();
        return true;
    } else {
        // エラーレスポンス
        Serial.println("Error on http request");
        http_client.end();
        return false;
    }
}
#endif