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
    _notification_text = new String("");
    _notification_time_limit = 0;
};

void Display_Manager::uploadDisplayBuffer(LGFX_Sprite* buffer,int x_loc,int y_loc) {
    _notification_sprite.deleteSprite();
    if (_notification == true) {
        if ((millis() - _notification_timer_start) * 1000 < *_notification_time_limit)  {
            drawNotificationText(buffer,x_loc,y_loc);
        } else {
            _notification = false;

        }
    }
    lcd.pushImageDMA(x_loc,y_loc,buffer->width(),buffer->height(),buffer->getBuffer());
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

void Display_Manager::sendNotification(String* notification,unsigned long* time_limit) {
    _notification_text = notification;
    _notification_time_limit = time_limit;
    _notification = true;
}

void Display_Manager::error(String error) {
    lcd.fillScreen(TFT_BLUE);
    drawTextToDisplay(error,TFT_WHITE,45,int(_height/3));
}

void Display_Manager::drawNotificationText(LGFX_Sprite* buffer,int x, int y) {
    _notification_sprite.createSprite(NOTIFICATION_WIDTH,NOTIFICATION_HEIGHT);
    _notification_sprite.setTextColor(TFT_WHITE);
    _notification_sprite.setTextSize(NOTIFICATION_TEXT_SIZE);
    _notification_sprite.setCursor(x,y);
    _notification_sprite.print(*_notification_text);
    buffer->pushImageDMA(_width,_height,NOTIFICATION_WIDTH,NOTIFICATION_HEIGHT,_notification_sprite.getBuffer());
}

void Display_Manager::drawTextToDisplay(String text,int forground,int x,int y) {
    lcd.setTextColor(TFT_WHITE);
    lcd.setTextSize(2);
    lcd.setCursor(x, y);
    lcd.print(text);
};
