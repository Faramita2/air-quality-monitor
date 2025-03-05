#include "display_init.h"

TFT_eSPI tft = TFT_eSPI();

// LVGL 刷新缓冲区大小
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[480 * 20]; // 缓冲区大小为屏幕宽度 × 20 行

// LVGL 显示刷新回调函数
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area,
                   lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();
  // 告诉 LVGL 刷新完成
  lv_disp_flush_ready(disp);
}

bool initialize_display() {
  // 初始化 TFT 屏幕
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

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