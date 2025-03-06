// DataUploader.cpp

#include "DataUploader.h"

DataUploader &DataUploader::getInstance() {
  static DataUploader instance;
  return instance;
}

DataUploader::DataUploader() {}

DataUploader::~DataUploader() {}

bool DataUploader::init() {
  _serverUrl = THINGSPEAK_SERVER_URL;
  _apiKey = THINGSPEAK_WRITE_API_KEY;
  return true;
}

bool DataUploader::upload(float temperature, float humidity) {
  // 检查 WiFi 是否连接
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi is disconnected, cannot upload data.");
    return false;
  }

  HTTPClient http;

  String url = _serverUrl;
  url += "?api_key=" + String(_apiKey);
  url += "&field1=" + String(temperature);
  url += "&field2=" + String(humidity);

  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.printf("HTTP Response Code: %d\n", httpResponseCode);

    String response = http.getString();
    Serial.printf("Server Response: %s\n", response.c_str());

    if (httpResponseCode == 200) { // ThingSpeak 成功写入时通常返回 "0"
      Serial.println("Data uploaded successfully.");
      http.end();
      return true;
    } else {
      Serial.println(
          "Data upload failed. Check the server response for details.");
      http.end();
      return false;
    }
  } else {
    Serial.printf("HTTP GET request failed, error code: %d\n",
                  httpResponseCode);
    http.end();
    return false;
  }
}