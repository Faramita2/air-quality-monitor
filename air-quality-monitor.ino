#include "i2c_config.h"
#include "sensor.h"
#include "sht31_test.h"
#include <Arduino.h>
#include <Wire.h>

void setup() {
  // 初始化串口通信
  Serial.begin(115200);

  // 初始化 I2C
  initI2C();

  // 初始化传感器
  initSensor();
}

void loop() { sht31_test(); }