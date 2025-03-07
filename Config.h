// Config.h

#ifndef CONFIG_H
#define CONFIG_H

// debug ?
#define APP_DEBUG_MODE 0

// dev: 40s
#define UPLOAD_TIME_GAP 40 * 1000
// prod: 5min
// #define UPLOAD_TIME_GAP 5 * 60 * 1000

// 定义 SHT31 I2C 引脚
#define SDA_PIN 18
#define SCL_PIN 19

// WiFi 配置
extern const char *WIFI_SSID;
extern const char *WIFI_PASSWORD;

// ThingSpeak 配置
extern const char *THINGSPEAK_SERVER_URL;
extern const char *THINGSPEAK_WRITE_API_KEY;
extern const char *THINGSPEAK_READ_API_KEY;

#endif