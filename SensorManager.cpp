// SensorManager.cpp

#include "SensorManager.h"

SensorManager &SensorManager::getInstance() {
  static SensorManager instance;
  return instance;
}

SensorManager::SensorManager() {}

SensorManager::~SensorManager() {}

bool SensorManager::init() {
  Wire.begin();

  Serial.println("Initializing SHT31...");
  if (!sht31.begin(0x44)) {
    Serial.println("Initialization failed: cannot find SHT31 sensor, check "
                   "connection please!");
    return false;
  } else {
    Serial.println("SHT31 initialized.");
  }

  // if (!co2Sensor.begin()) {
  //     Serial.println("Initialization failed: cannot find CO2 sensor, check
  //     connection please!"); return false;
  // } else {
  //     Serial.println("CO2 sensor initialized.");
  // }

  return true;
}

float SensorManager::readTemperature() {
  float temperature = sht31.readTemperature();
  if (APP_DEBUG_MODE) {
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.println("°C");
  }
  return temperature;
}

float SensorManager::readHumidity() {
  float humidity = sht31.readHumidity();
  if (APP_DEBUG_MODE) {
    Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    Serial.println("%");
  }
  return humidity;
}

// float SensorManager::readCO2() {
//     float co2 = co2Sensor.read();
//     Serial.print("CO2: ");
//     Serial.print(co2, 2);
//     Serial.println("ppm");
//     return co2;
// }