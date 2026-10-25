#pragma once

#include <Arduino.h>
#include <String>

#include "config.h"
#include "display_config.h"
#include "services.h"

class Display_Manager {
public:
    
    Display_Manager(System& system_services,uint16_t width, uint16_t height);

    void begin();

    //Display info
    int getDisplayWidth();
    int getDisplayHeight();

    //Display operations
    void fill(uint16_t color);
    void uploadDisplayBuffer(LGFX_Sprite* sprite,int x_loc,int y_loc);
    void sendNotification(String* notification,unsigned long* time_limit);
    void displayNotification();
    void error(String error);
    bool setBackground(LGFX_Sprite sprite);

private:
    void drawTextToDisplay(String text,int forground,int x,int y);
    void drawNotificationText(LGFX_Sprite* buffer, int x, int y);

    //Window width and height
    uint16_t _width;
    uint16_t _height;

    //Allows this to call functions from around the system if needed
    System& _system_services;

    //Notification display data
    bool _notification;
    String* _notification_text;
    time_t _notification_timer_start = 0;
    LGFX_Sprite _notification_sprite;
    unsigned long* _notification_time_limit;
};
