// DataUploader.h

#ifndef DATA_UPLOADER_H
#define DATA_UPLOADER_H

#include "Config.h"
#include <HTTPClient.h>
#include <WiFi.h>

class DataUploader {
public:
  static DataUploader &getInstance();
  bool init();
  bool upload(float temperature, float humidity);

private:
  DataUploader();
  ~DataUploader();
  friend class SystemManager;
  DataUploader(const DataUploader &) = delete;
  DataUploader &operator=(const DataUploader &) = delete;

  const char *_serverUrl;
  const char *_apiKey;
};

#endif