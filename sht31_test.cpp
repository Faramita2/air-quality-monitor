#include "sensor.h"

void sht31_test() {
  float temperature = readTemperature();
  float humidity = readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("读取传感器数据失败！");
    return;
  }

  // 打印温度和湿度数据到串口监视器
  Serial.print("温度: ");
  Serial.print(temperature);
  Serial.print(" °C, 湿度: ");
  Serial.print(humidity);
  Serial.println(" %");

  // 延迟一段时间（例如 2 秒）
  delay(2000);
}