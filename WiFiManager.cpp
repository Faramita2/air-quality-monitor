// WiFiManager.cpp

#include "WiFiManager.h"

WiFiManager &WiFiManager::getInstance() {
  static WiFiManager instance;
  return instance;
}

WiFiManager::WiFiManager() {}

WiFiManager::~WiFiManager() {}

bool WiFiManager::init() {
  _ssid = WIFI_SSID;
  _password = WIFI_PASSWORD;
  return true;
}

bool WiFiManager::connect() {
  WiFi.begin(_ssid, _password);
  Serial.println("Connecting WiFi...");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    return true;
  } else {
    Serial.println("\nFailed to connect WiFi.");
    return false;
  }
}

bool WiFiManager::isConnected() { return WiFi.status() == WL_CONNECTED; }