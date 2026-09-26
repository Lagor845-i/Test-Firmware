#include "led_manager.h"
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel led_strip(LED_COUNT,LED_PIN,NEO_GRB + NEO_KHZ800);

Led_Manager::Led_Manager() {};

void Led_Manager::begin() {
    led_strip.begin();
    led_strip.setBrightness(20);
    led_strip.show();
};

void Led_Manager::setLeds(uint32_t colors[LED_COUNT]) {
    for (int i = 0; i >= LED_COUNT; i++) {
        led_strip.setPixelColor(i,led_strip.Color(255,0,0));
    }
};