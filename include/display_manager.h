#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

class Display_Manager {
public:
    Display_Manager(uint16_t width, uint16_t height);

    void begin();
    void fill(uint16_t color);

private:
    uint16_t _width;
    uint16_t _height;
};
