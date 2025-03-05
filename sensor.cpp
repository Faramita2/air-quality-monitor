#include "sensor.h"
#include <Adafruit_SHT31.h>
#include <Wire.h>

Adafruit_SHT31 sht31;

bool initSensors() {
  Wire.begin();
  Serial.println("Initializing SHT31...");
  if (!sht31.begin(0x44)) {
    Serial.println("Initialized failed: can not find SHT31 sensor, check "
                   "connection please!");
    return false;
  } else {
    Serial.println("SHT31 initialized.");
    return true;
  }
}

float readTemperature() {
  float temperature = sht31.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.print("°C, ");
  return temperature;
}

float readHumidity() {
  float humidity = sht31.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity, 2);
  Serial.println("%");
  return humidity;
}