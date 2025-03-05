#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "SensorDisplay.h"

class SystemManager {
public:
  static SystemManager &getInstance();
  void init();
  void update();

private:
  SensorDisplay sensorDisplay;

  SystemManager();
  ~SystemManager();
};
#endif