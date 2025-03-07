// SensorManager.h

#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Adafruit_CCS811.h>
#include <Adafruit_SHT31.h>
#include <Config.h>
#include <Wire.h>

class SensorManager {
public:
  static SensorManager &getInstance();
  bool init();
  float readTemperature();
  float readHumidity();
  bool readCO2AndTVOC(float &co2, float &tvoc);
  // float readPM25();

private:
  SensorManager();
  ~SensorManager();
  friend class SystemManager;
  SensorManager(const SensorManager &) = delete;
  SensorManager &operator=(const SensorManager &) = delete;

  Adafruit_SHT31 sht31;
  Adafruit_CCS811 ccs811;
  // CO2Sensor co2Sensor;
  // PM25Sensor pm25Sensor;
};

#endif