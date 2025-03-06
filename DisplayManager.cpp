// DisplayManager.cpp

#include "DisplayManager.h"
#include "lvgl_helpers.h"
#include <Arduino.h>

// LVGL 刷新缓冲区大小
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[480 * 20]; // 缓冲区大小为屏幕宽度 × 20 行

// LVGL 显示刷新回调函数
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area,
                   lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  DisplayManager &displayManager =
      DisplayManager::getInstance(); // 获取单例实例
  displayManager.getTFT().startWrite();
  displayManager.getTFT().setAddrWindow(area->x1, area->y1, w, h);
  displayManager.getTFT().pushColors((uint16_t *)&color_p->full, w * h, true);
  displayManager.getTFT().endWrite();

  // 告诉 LVGL 刷新完成
  lv_disp_flush_ready(disp);
}

DisplayManager &DisplayManager::getInstance() {
  static DisplayManager instance;
  return instance;
}

DisplayManager::DisplayManager() {}

DisplayManager::~DisplayManager() {}

bool DisplayManager::init() {
  // 初始化 TFT 屏幕
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  // 初始化 LVGL
  lv_init();

  // 初始化显示缓冲区
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, 480 * 20);

  // 初始化显示驱动
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 480;
  disp_drv.ver_res = 320;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;

  // 注册显示驱动
  lv_disp_drv_register(&disp_drv);

  return true;
}

// 更新显示内容
void DisplayManager::update(float temperature, float humidity) {
  // 示例：更新传感器数据显示（可以根据需要自定义）
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "Temp: %.2f°C\nHumidity: %.2f%%",
           temperature, humidity);

  // 清空屏幕并显示新数据
  lv_obj_clean(lv_scr_act()); // 清空当前屏幕
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, buffer);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

// 显示欢迎消息
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

// 获取 TFT 实例（用于刷新回调函数）
TFT_eSPI &DisplayManager::getTFT() { return tft; }