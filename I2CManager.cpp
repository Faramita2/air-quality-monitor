// I2CManager.cpp

#include "I2CManager.h"
#include "Config.h"
#include <Arduino.h>

I2CManager &I2CManager::getInstance() {
  static I2CManager instance;
  return instance;
}

I2CManager::I2CManager() {}

I2CManager::~I2CManager() {}

bool I2CManager::init() {
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.println("Scanning I2C bus...");
  int deviceCount = 0;
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.printf("Found device at address 0x%02X\n", address);
      deviceCount++;
    }
  }
  if (deviceCount == 0) {
    Serial.println("No I2C devices found.");
  }
  return true;
}