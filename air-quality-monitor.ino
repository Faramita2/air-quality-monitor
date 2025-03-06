// air-quality-monitor.ino

#include "SystemManager.h"
#include <Arduino.h>

void lvgl_task(void *pvParameters) {
  while (1) {
    lv_timer_handler();           // 处理 LVGL 事件
    vTaskDelay(pdMS_TO_TICKS(5)); // 每 5ms 调用一次
  }
}

SystemManager &systemManager = SystemManager::getInstance();

void setup() {
  systemManager.init();
  xTaskCreatePinnedToCore(lvgl_task, "LVGL Task", 8 * 1024, NULL, 1, NULL, 1);
}

void loop() {
  systemManager.update();

  delay(5000);
}