// SystemManager.h

#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "DataUploader.h"
#include "DisplayManager.h"
#include "I2CManager.h"
#include "SensorManager.h"
#include "WiFiManager.h"

class SystemManager {
public:
  static SystemManager &getInstance();
  void init();
  void update();

private:
  SystemManager();
  ~SystemManager();

  SystemManager(const SystemManager &) = delete;
  SystemManager &operator=(const SystemManager &) = delete;

  DisplayManager displayManager;
  SensorManager sensorManager;
  WiFiManager wifiManager;
  DataUploader dataUploader;
  I2CManager i2CManager;

  unsigned long lastUploadTime = 0;
};
#endif