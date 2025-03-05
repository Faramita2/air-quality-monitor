#include "sensor.h"
#include <Adafruit_SHT31.h>
#include <Wire.h>

Adafruit_SHT31 sht31;

void initSensor() {
  Wire.begin();
  if (!sht31.begin(0x44)) {
    Serial.println("无法找到 SHT31 传感器，请检查连接！");
    while (1)
      ;
  } else {
    Serial.println("SHT31 传感器初始化成功！");
  }
}

float readTemperature() { return sht31.readTemperature(); }

float readHumidity() { return sht31.readHumidity(); }