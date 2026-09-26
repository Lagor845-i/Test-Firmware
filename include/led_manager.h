#pragma once
#include <Adafruit_NeoPixel.h>

#define LED_PIN 7
#define LED_COUNT 23

extern Adafruit_NeoPixel led_strip; 

class Led_Manager {
    public:
        Led_Manager();
        void begin();
        void setLeds(uint32_t colors[LED_COUNT]);
};