#pragma once

#include <Arduino.h>
#include <String>

#include "display_config.h"
#include "services.h"

class Display_Manager {
public:
    
    Display_Manager(System& system_services,uint16_t width, uint16_t height);

    void begin();
    void fill(uint16_t color);

    void display();
    void enableBackground();
    void disableBackground();
    void uploadSprite(LGFX_Sprite sprite,int x_loc,int y_loc);

    void displayNotification();
    void error(String error);

    void drawText(String text,int forground,int x,int y);
    bool setBackground(LGFX_Sprite sprite);

private:
    uint16_t _width;
    uint16_t _height;
    System& _system_services;
    LGFX_Sprite _buffer1;
    LGFX_Sprite _buffer2;
    LGFX_Sprite _background;
    bool _background_active;
    bool _current_buffer;
};
