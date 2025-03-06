// I2CManager.h

#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

#include "Config.h"
#include <Wire.h>

class I2CManager {
public:
  static I2CManager &getInstance();
  bool init();

private:
  I2CManager();
  ~I2CManager();
  friend class SystemManager;
  I2CManager(const I2CManager &) = delete;
  I2CManager &operator=(const I2CManager &) = delete;
};

#endif