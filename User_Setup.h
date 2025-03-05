#define ST7796_DRIVER
#define TFT_WIDTH 480
#define TFT_HEIGHT 320

#define TFT_CS 15
#define TFT_DC 2
#define TFT_RST 4
#define TFT_MOSI 11
#define TFT_SCLK 12
// 不定义 TFT_BL，因为 LED 已接 5V

#define SPI_FREQUENCY 8000000
#define TFT_DEBUG