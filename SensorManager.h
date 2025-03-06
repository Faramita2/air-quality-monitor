// SensorManager.h

#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Adafruit_SHT31.h>
#include <Config.h>
#include <Wire.h>

class SensorManager {
public:
  static SensorManager &getInstance();
  bool init();
  float readTemperature();
  float readHumidity();
  // float readCO2();
  // float readPM25();

private:
  SensorManager();
  ~SensorManager();
  friend class SystemManager;
  SensorManager(const SensorManager &) = delete;
  SensorManager &operator=(const SensorManager &) = delete;

  Adafruit_SHT31 sht31;
  // CO2Sensor co2Sensor;
  // PM25Sensor pm25Sensor;
};

#endif