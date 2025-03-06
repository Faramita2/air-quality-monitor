#include "DisplayManager.h"

DisplayManager &DisplayManager::getInstance() {
  static DisplayManager instance;
  return instance;
}

DisplayManager::DisplayManager() {}

DisplayManager::~DisplayManager() {}

bool DisplayManager::init() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  lvglHelper.init(getTFT());

  return true;
}

void DisplayManager::update(float temperature, float humidity) {
  lvglHelper.updateSensorData(temperature, humidity);
}

void DisplayManager::showWelcomeMessage() {
  welcomeLabel = lv_label_create(lv_scr_act());
  lv_label_set_text(welcomeLabel, "Welcome!");
  lv_obj_align(welcomeLabel, LV_ALIGN_CENTER, 0, 0);

  lv_obj_set_style_opa(welcomeLabel, LV_OPA_TRANSP, LV_PART_MAIN);

  lv_anim_t anim;
  lv_anim_init(&anim);
  lv_anim_set_var(&anim, welcomeLabel);
  lv_anim_set_exec_cb(&anim, [](void *obj, int32_t value) {
    lv_obj_set_style_opa((lv_obj_t *)obj, value, LV_PART_MAIN);
  });
  lv_anim_set_values(&anim, LV_OPA_TRANSP, LV_OPA_COVER);
  lv_anim_set_time(&anim, 1000);
  lv_anim_start(&anim);

  delay(2000);

  lv_anim_set_values(&anim, LV_OPA_COVER, LV_OPA_TRANSP);
  lv_anim_start(&anim);

  delay(1000);

  lv_obj_del(welcomeLabel);
  welcomeLabel = nullptr;
}

TFT_eSPI &DisplayManager::getTFT() { return tft; }