// LVGLHelper.cpp

#include "LVGLHelper.h"

LVGLHelper::LVGLHelper() {}

LVGLHelper::~LVGLHelper() {}

static TFT_eSPI tftInstance;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area,
                   lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tftInstance.startWrite();
  tftInstance.setAddrWindow(area->x1, area->y1, w, h);
  tftInstance.pushColors((uint16_t *)&color_p->full, w * h, true);
  tftInstance.endWrite();

  lv_disp_flush_ready(disp);
}

bool LVGLHelper::init(TFT_eSPI &tft) {
  tftInstance = tft;

  lv_init();
  // 初始化显示缓冲区
  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf[480 * 20]; // 缓冲区大小为屏幕宽度 × 20 行
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, 480 * 20);

  // 初始化显示驱动
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 480;            // 屏幕宽度
  disp_drv.ver_res = 320;            // 屏幕高度
  disp_drv.flush_cb = my_disp_flush; // 设置刷新回调函数
  disp_drv.draw_buf = &draw_buf;

  // 注册显示驱动
  lv_disp_drv_register(&disp_drv);
  return true;
}

void LVGLHelper::updateSensorData(float temperature, float humidity, float co2,
                                  float tvoc) {
  if (!tempLabel) {
    tempLabel = lv_label_create(lv_scr_act());
    lv_obj_align(tempLabel, LV_ALIGN_TOP_LEFT, 10, 10);
  }
  if (!humidityLabel) {
    humidityLabel = lv_label_create(lv_scr_act());
    lv_obj_align(humidityLabel, LV_ALIGN_TOP_LEFT, 10, 50);
  }
  if (!co2Label) {
    co2Label = lv_label_create(lv_scr_act());
    lv_obj_align(co2Label, LV_ALIGN_TOP_LEFT, 10, 90);
  }
  if (!tvocLabel) {
    tvocLabel = lv_label_create(lv_scr_act());
    lv_obj_align(tvocLabel, LV_ALIGN_TOP_LEFT, 10, 130);
  }

  char tempBuffer[50];
  snprintf(tempBuffer, sizeof(tempBuffer), "Temperature: %.2f°C", temperature);
  lv_label_set_text(tempLabel, tempBuffer);

  char humidityBuffer[50];
  snprintf(humidityBuffer, sizeof(humidityBuffer), "Humidity: %.2f%%",
           humidity);

  char co2Buffer[50];
  if (co2 == -1) {
    snprintf(co2Buffer, sizeof(co2Buffer), "CO2: N/A");
  } else {
    snprintf(co2Buffer, sizeof(co2Buffer), "CO2: %.2fppm", co2);
  }

  char tvocBuffer[50];
  if (tvoc == -1) {
    snprintf(tvocBuffer, sizeof(tvocBuffer), "TVOC: N/A");
  } else {
    snprintf(tvocBuffer, sizeof(tvocBuffer), "TVOC: %.2fppb", tvoc);
  }

  lv_label_set_text(tempLabel, tempBuffer);

  lv_label_set_text(humidityLabel, humidityBuffer);

  lv_label_set_text(co2Label, co2Buffer);

  lv_label_set_text(tvocLabel, tvocBuffer);
}

void LVGLHelper::displayText(const char *text, int x, int y, lv_color_t color) {
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, text);
  lv_obj_set_style_text_color(label, color, LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, x, y);
}