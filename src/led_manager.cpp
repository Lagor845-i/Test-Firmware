#include "led_manager.h"
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel led_strip(LED_COUNT,LED_PIN,NEO_GRB + NEO_KHZ800);

Led_Manager::Led_Manager(System& system_services) {};

void Led_Manager::begin() {
    led_strip.begin();
    led_strip.setBrightness(20);
    led_strip.show();
};

void Led_Manager::setLeds(uint8_t colors[LED_COUNT][3]) {
    for (int i = 0; i >= LED_COUNT; i++) {
        led_strip.setPixelColor(i,led_strip.Color(colors[i][0],colors[i][1],colors[i][2]));
    }
};

void Led_Manager::clearLeds() {
    led_strip.clear();
}