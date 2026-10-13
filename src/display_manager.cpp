#include "display_manager.h"

Display_Manager::Display_Manager(System& system_services,uint16_t width, uint16_t height)
    : _width(width),
      _height(height),
      _system_services(system_services) {
};

void Display_Manager::begin() {
    lcd.init();
    lcd.initDMA();
    lcd.setRotation(3);
    lcd.fillScreen(TFT_BLACK);
    _system_services.systemLog("Display Initialized");
    _current_buffer = true;
    _background_active = false;
};

void Display_Manager::uploadSprite(LGFX_Sprite sprite,int x_loc,int y_loc) {
    lcd.pushImageDMA(x_loc,y_loc,sprite.width(),sprite.height(),sprite.getBuffer());
}

void Display_Manager::fill(uint16_t color) {
    lcd.fillScreen(color);
};

void Display_Manager::error(String error) {
    lcd.fillScreen(TFT_BLUE);
    drawText(error,TFT_WHITE,45,int(_height/3));
}

void Display_Manager::drawText(String text,int forground,int x,int y) {
    lcd.setTextColor(TFT_WHITE);
    lcd.setTextSize(2);
    lcd.setCursor(x, y);
    lcd.print(text);
};
