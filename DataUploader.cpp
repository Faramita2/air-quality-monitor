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
    Serial.printf("Data uploaded successfully, status code: %d\n",
                  httpResponseCode);
    http.end();
    return true;
  } else {
    Serial.printf("Data uploaded failed, error code: %d\n", httpResponseCode);
    http.end();
    return false;
  }
}