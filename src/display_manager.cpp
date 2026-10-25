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
    _notification = true;
    _notification_text = "";
    _notification_time_limit = 0;
};

void Display_Manager::setDisplayBuffer(LGFX_Sprite* buffer) {
    _display_buffer = buffer;
}

void Display_Manager::updateDisplay() {
    _notification_sprite.deleteSprite();
    if (_notification == true) {
        if ((millis() - _notification_timer_start) * 1000 < _notification_time_limit)  {
            drawNotificationText();
        } else {
            _notification = false;
        }
    }
    lcd.pushImageDMA(0,0,_display_buffer->width(),_display_buffer->height(),_display_buffer->getBuffer());
}

void Display_Manager::fill(uint16_t color) {
    lcd.fillScreen(color);
};

int Display_Manager::getDisplayWidth() {
    return _width;
}

int Display_Manager::getDisplayHeight() {
    return _height;
}

void Display_Manager::sendNotification(String notification,int time_limit) {
    _notification_text = notification;
    _notification_time_limit = time_limit;
    _notification = true;
}

void Display_Manager::error(String error) {
    lcd.fillScreen(TFT_BLUE);
    drawTextToDisplay(error,TFT_WHITE,45,int(_height/3));
}

void Display_Manager::drawNotificationText() {
    int notification_width = NOTIFICATION_PIXELS_PER_CHARACTER * _notification_text.length();
    _notification_sprite.createSprite(notification_width,NOTIFICATION_HEIGHT);
    _notification_sprite.setTextColor(TFT_WHITE);
    _notification_sprite.setTextSize(NOTIFICATION_TEXT_SIZE);
    _notification_sprite.setCursor(SCREEN_WIDTH - notification_width - NOTIFICATION_X_OFFSET,SCREEN_HEIGHT - NOTIFICATION_HEIGHT - NOTIFICATION_Y_HEIGHT);
    _notification_sprite.print(_notification_text);
    _display_buffer->pushImageDMA(_width,_height,notification_width,NOTIFICATION_HEIGHT,_notification_sprite.getBuffer());
}

void Display_Manager::drawTextToDisplay(String text,int forground,int x,int y) {
    lcd.setTextColor(TFT_WHITE);
    lcd.setTextSize(2);
    lcd.setCursor(x, y);
    lcd.print(text);
};
