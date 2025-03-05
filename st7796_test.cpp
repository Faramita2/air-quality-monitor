#include "st7796_test.h"
#include <Arduino.h>
#include <SPI.h>

void initST7796(TFT_eSPI &tft) {
  Serial.println("Starting TFT test...");

  Serial.println("TFT_CS: " + String(TFT_CS));
  Serial.println("TFT_DC: " + String(TFT_DC));
  Serial.println("TFT_RST: " + String(TFT_RST));
  Serial.println("TFT_MOSI: " + String(TFT_MOSI));
  Serial.println("TFT_SCLK: " + String(TFT_SCLK));
  Serial.println("SPI Frequency: " + String(SPI_FREQUENCY));

  Serial.println("Initializing TFT...");
  tft.init();
  Serial.println("TFT initialized");

  tft.setRotation(1);
}

void displayTest(TFT_eSPI &tft) {
  tft.fillScreen(TFT_BLACK);
  Serial.println("Screen cleared");

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  tft.setCursor(0, 0);
  tft.println("TFT Test OK");
  tft.println("Resolution: 480x320");
  Serial.println("Text displayed");
}