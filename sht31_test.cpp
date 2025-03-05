#include "sht31_test.h"

void sht31_test() {
  Serial.println("Reading data from sht31...");
  float temperature = readTemperature();
  float humidity = readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Read data from sht31 failed!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(5000);
}