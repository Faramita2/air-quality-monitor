#ifndef LVGL_HELPERS_H
#define LVGL_HELPERS_H

#include <lvgl.h>
#include <cstdio>

void display_text(const char *text, int x, int y, lv_color_t color);

void update_sht31_sensor_data(float temperature, float humidity);

#endif