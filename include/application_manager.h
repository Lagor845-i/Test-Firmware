#pragma once

#include <esp_elf.h>
#include <Arduino.h>
#include <string>

#include "config.h"
#include "services.h"
#include "core_api.h"

class Application_Manager {
  public:
    Application_Manager(QueueHandle_t* queue);
    bool Start();
    

    //Api calls from application
    bool requestFile(String file_loc);
    bool selectApplication(String app_location);
    bool quitApplication();
  
  private:
    bool callApi(queueItem item);
    bool loadFile(File file);

    App* _app_services;
    String app_folder;
    String boot_app_location = BOOT_APP;
    String menu_app_location = BOOT_MENU;
    esp_elf_t current_app;
    String _change_app_to;
    uint8_t* _elf_buffer;
    bool _quit_app = false;
    QueueHandle_t _process_queue_in;
    QueueHandle_t _process_queue_out;
};