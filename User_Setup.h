#define ST7796_DRIVER
#define TFT_WIDTH 480
#define TFT_HEIGHT 320

#define TFT_CS 15
#define TFT_DC 2
#define TFT_RST 4
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_MISO -1 // 禁用 MISO
// 不定义 TFT_BL，因为 LED 已接 5V

#define SPI_FREQUENCY 4000000
#define TFT_DEBUG