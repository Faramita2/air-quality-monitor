#include "sht31_test.h"
#include <Arduino.h>

void sht31_test() {
  float temperature = readTemperature();
  float humidity = readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("读取传感器数据失败！");
    return;
  }

  Serial.print("温度: ");
  Serial.print(temperature);
  Serial.print(" °C, 湿度: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(5000);
}