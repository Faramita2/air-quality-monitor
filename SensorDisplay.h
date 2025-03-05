#ifndef SENSOR_DISPLAY_H
#define SENSOR_DISPLAY_H

#include <lvgl.h>

class SensorDisplay {
public:
  void update();
  void showWelcomeMessage();

private:
  lv_obj_t *welcomeLabel = nullptr;
};

#endif