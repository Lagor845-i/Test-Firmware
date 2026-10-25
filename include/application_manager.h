#pragma once

#include <esp_elf.h>
#include <Arduino.h>
#include <string.h>

#include "config.h"
#include "services.h"
#include "core_api.h"
#include "os.h"
#include "elf_symbols.h"

class Application_Manager {
  public:
    Application_Manager(crossCoreBuffers* buffers);
    void Start();
    
    //Api calls from application
    bool requestELFFile(String file_loc);
    bool quitApplication();
    bool printToConsole(String text);
    bool printToConsoleApp(String text);
  
  private:
    bool isElf(File file);
    bool bootFile(uint8_t* file_bytes);
    uint8_t* recieveElfFile();
    File* recieveFile();
    bool sendAppApi();

    osApi* _app_services;
    crossCoreBuffers* _cross_core_buffers;
    String app_folder;
    esp_elf_t current_app;
    String _change_app_to;
    uint8_t* _elf_buffer;
};