// I2CManager.cpp

#include "I2CManager.h"
#include "Config.h"

I2CManager &I2CManager::getInstance() {
  static I2CManager instance;
  return instance;
}

I2CManager::I2CManager() {}

I2CManager::~I2CManager() {}

bool I2CManager::init() {
  Wire.begin(SDA_PIN, SCL_PIN);
  return true;
}