#include "display_manager.h"

#define TFT_CS    0
#define TFT_DC    45
#define TFT_RST   1
#define TFT_MISO  -1
#define TFT_MOSI  3
#define TFT_SCLK  46

SPIClass displaySPI(FSPI);

Adafruit_ST7789 display(
    //&displaySPI,
    TFT_CS,
    TFT_DC,
    TFT_RST
);

Display_Manager::Display_Manager(uint16_t width, uint16_t height)
    : _width(width),
      _height(height) {

    }

void Display_Manager::begin() {
    displaySPI.begin(
        TFT_SCLK,
        -1,        // MISO unused
        TFT_MOSI,
        TFT_CS
    );

    display.init(_width, _height);
    display.setRotation(1);
    display.fillScreen(ST77XX_BLUE);
}

void Display_Manager::fill(uint16_t color) {
    display.fillScreen(color);
}
