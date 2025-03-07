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

  Serial.println("Initializing CCS811...");
  int attempts = 0;
  while (!ccs811.begin(0x5B) && attempts < 5) {
    Serial.println("CCS811 initialization failed, retrying...");
    delay(1000);
    attempts++;
  }

  if (attempts >= 5) {
    Serial.println("Initialization failed: cannot find CCS811 sensor, check "
                   "connection please!");
    return false;
  } else {
    Serial.println("Waiting CCS811 to be ready...");

    while (!ccs811.available())
      ;
    Serial.println("CCS811 is ready...");

    Serial.println("CCS811 initialized.");
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

bool SensorManager::readCO2AndTVOC(float &co2, float &tvoc) {
  if (ccs811.available()) {
    if (!ccs811.readData()) {
      co2 = ccs811.geteCO2();
      tvoc = ccs811.getTVOC();
      if (APP_DEBUG_MODE) {
        Serial.print("CO2: ");
        Serial.print(co2, 2);
        Serial.println("ppm");
        Serial.print("TVOC: ");
        Serial.print(tvoc, 2);
        Serial.println("ppb");
      }
      return true;
    } else {
      Serial.println("ERROR! CSS811 cannot read data.");
      return false;
    }
  } else {
    Serial.println("CCS811 data not available.");
    return false;
  }
}