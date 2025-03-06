// WiFiManager.h

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include "Config.h"
#include <WiFi.h>

class WiFiManager {
public:
  static WiFiManager &getInstance();

  bool init();
  bool connect();
  bool isConnected();

private:
  WiFiManager();
  ~WiFiManager();
  friend class SystemManager;
  WiFiManager(const WiFiManager &) = delete;
  WiFiManager &operator=(const WiFiManager &) = delete;

  const char *_ssid;
  const char *_password;
};

#endif