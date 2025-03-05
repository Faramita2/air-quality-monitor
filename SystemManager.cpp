#include "SystemManager.h"
#include "display_init.h"
#include "i2c_config.h"
#include "lvgl_helpers.h"
#include "sensor.h"
#include <lvgl.h>

SystemManager &SystemManager::getInstance() {
  static SystemManager instance;
  return instance;
}

void SystemManager::init() {
  Serial.begin(115200);
  Serial.println("Initializing system...");

  //   lv_obj_t *progressBar = lv_bar_create(lv_scr_act());
  //   lv_obj_set_size(progressBar, 200, 20);
  //   lv_obj_align(progressBar, LV_ALIGN_CENTER, 0, 0);
  //   lv_bar_set_value(progressBar, 0, LV_ANIM_OFF);

  Serial.println("Initializing display...");
  if (!initialize_display()) {
    Serial.println("Error: Failed to initialize display.");
    while (1)
      ;
  }
  Serial.println("Display initialized.");
  //   lv_bar_set_value(progressBar, 25, LV_ANIM_ON);

  Serial.println("Initializing I2C...");
  if (!initI2C()) {
    Serial.println("Error: Failed to initialize I2C.");
    while (1)
      ;
  }
  Serial.println("I2C initialized.");
  //   lv_bar_set_value(progressBar, 50, LV_ANIM_ON);

  Serial.println("Initializing Sensors...");
  if (!initSensors()) {
    Serial.println("Error: Failed to initialize sensors.");
    while (1)
      ;
  }
  Serial.println("Sensors initialized.");
  //   lv_bar_set_value(progressBar, 100, LV_ANIM_ON);

  sensorDisplay.showWelcomeMessage();
  Serial.println("System ready.");
  delay(2000);

  //   lv_obj_del(progressBar);
}

void SystemManager::update() { sensorDisplay.update(); }

SystemManager::SystemManager() {}

SystemManager::~SystemManager() {}