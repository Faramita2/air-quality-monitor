// LVGLHelper.h

#ifndef LVGL_HELPER_H
#define LVGL_HELPER_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

class LVGLHelper {
public:
  LVGLHelper();
  ~LVGLHelper();

  bool init(TFT_eSPI &tft);

  void updateSensorData(float temperature, float humidity);

  void displayText(const char *text, int x, int y, lv_color_t color);

private:
  lv_obj_t *tempLabel = nullptr;
  lv_obj_t *humidityLabel = nullptr;
};

#endif