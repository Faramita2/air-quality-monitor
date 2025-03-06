// DisplayManager.h

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "LVGLHelper.h"
#include <TFT_eSPI.h>
#include <lvgl.h>

class DisplayManager {
public:
  static DisplayManager &getInstance();
  bool init();
  void update(float temperature, float humidity);
  void showWelcomeMessage();
  TFT_eSPI &getTFT();

private:
  DisplayManager();
  ~DisplayManager();
  friend class SystemManager;
  DisplayManager(const DisplayManager &) = delete;
  DisplayManager &operator=(const DisplayManager &) = delete;

  LVGLHelper lvglHelper;
  lv_obj_t *welcomeLabel = nullptr;
  TFT_eSPI tft;
};

#endif