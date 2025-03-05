#include "i2c_config.h"
#include "sensor.h"
#include "sht31_test.h"
#include "st7796_test.h"
#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();
void setup() {
  Serial.begin(115200);

  initI2C();

  initSensor();

  initST7796(tft);
  displayTest(tft);
}

void loop() { sht31_test(); }