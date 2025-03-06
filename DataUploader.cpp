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

  char url[128];
  snprintf(url, sizeof(url), "%s?api_key=%s&field1=%.2f&field2=%.2f",
           _serverUrl, _apiKey, temperature, humidity);

  Serial.printf("Before HTTP: Free Heap = %d bytes\n", ESP.getFreeHeap());

  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.printf("HTTP Response Code: %d\n", httpResponseCode);

    String response = http.getString();
    Serial.printf("Server Response: %s\n", response.c_str());

    if (httpResponseCode == 200) {
      Serial.println("Data uploaded successfully.");
      http.end();
      Serial.printf("After HTTP: Free Heap = %d bytes\n", ESP.getFreeHeap());
      return true;
    } else {
      Serial.println(
          "Data upload failed. Check the server response for details.");
      http.end();

      Serial.printf("After HTTP: Free Heap = %d bytes\n", ESP.getFreeHeap());
      return false;
    }
  } else {
    Serial.printf("HTTP GET request failed, error code: %d\n",
                  httpResponseCode);
    http.end();

    Serial.printf("After HTTP: Free Heap = %d bytes\n", ESP.getFreeHeap());
    return false;
  }
}