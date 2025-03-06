// SystemManager.cpp

#include "SystemManager.h"
#include <Arduino.h>

SystemManager &SystemManager::getInstance() {
  static SystemManager instance;
  return instance;
}

SystemManager::SystemManager() {}

SystemManager::~SystemManager() {}

void SystemManager::init() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("----------------------------------------------------------");
  Serial.println("Initializing system...");

  Serial.println("Initializing display...");
  if (!displayManager.init()) {
    Serial.println("Error: Failed to initialize display.");
    while (1)
      ;
  }
  Serial.println("Display initialized.");

  Serial.println("Initializing I2C...");
  if (!i2CManager.init()) {
    Serial.println("Error: Failed to initialize I2C.");
    while (1)
      ;
  }
  Serial.println("I2C initialized.");

  Serial.println("Initializing Sensors...");
  if (!sensorManager.init()) {
    Serial.println("Error: Failed to initialize sensors.");
    while (1)
      ;
  }
  Serial.println("Sensors initialized.");

  Serial.println("Initializing Network...");
  if (!wifiManager.init()) {
    Serial.println("Error: Failed to initialize network.");
    while (1)
      ;
  }
  Serial.println("Network initialized.");

  Serial.println("Initializing Data Uploader...");
  if (!dataUploader.init()) {
    Serial.println("Error: Failed to initialize data uploader.");
    while (1)
      ;
  }
  Serial.println("Data uploader initialized.");

  displayManager.showWelcomeMessage();
  Serial.println("System ready.");
  Serial.println("----------------------------------------------------------");
  delay(2000);
}

void SystemManager::update() {
  unsigned long currentTime = millis();

  float temperature = sensorManager.readTemperature();
  float humidity = sensorManager.readHumidity();

  if (currentTime - lastUploadTime >= UPLOAD_TIME_GAP) {
    lastUploadTime = currentTime;

    if (!wifiManager.isConnected()) {
      Serial.println("WiFi disconnected, try to reconnect...");
      wifiManager.connect();
    }

    dataUploader.upload(temperature, humidity);
  }

  displayManager.update(temperature, humidity);
}