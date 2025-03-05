#include "lvgl_helpers.h"

static lv_obj_t *temp_label = nullptr;
static lv_obj_t *humidity_label = nullptr;

void display_text(const char *text, int x, int y, lv_color_t color) {
  // 创建一个标签对象
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, text);
  lv_obj_set_style_text_color(label, color, LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, x, y);
}

void update_sht31_sensor_data(float temperature, float humidity) {
  if (!temp_label) {
    temp_label = lv_label_create(lv_scr_act());
    lv_obj_align(temp_label, LV_ALIGN_TOP_LEFT, 10, 10);
  }
  if (!humidity_label) {
    humidity_label = lv_label_create(lv_scr_act());
    lv_obj_align(humidity_label, LV_ALIGN_TOP_LEFT, 10, 50);
  }

  // 格式化并更新温度和湿度
  char temp_buffer[50];
  sprintf(temp_buffer, "Temperature: %.2f°C", temperature);
  lv_label_set_text(temp_label, temp_buffer);

  char humidity_buffer[50];
  sprintf(humidity_buffer, "Humidity: %.2f%%", humidity);
  lv_label_set_text(humidity_label, humidity_buffer);
}