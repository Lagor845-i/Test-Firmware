/*

This file manages all of the api values for cross core communication
The queueItem struct at the bottom functions as a packet for whatever
data you want to send over to the other core. 

Since this system is using the other core to retrieve data and run in 
the background, you should be careful to request items before you need
them. This will keep down the latency in the application.

*/
#pragma once

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <os.h>

struct sendELFApi {
    bool new_api = false;
    osApi* os_api;
};

struct requestElfBuffer {
    bool new_request = false;
    String file_name;
    void* file_buffer;
};

struct elfBuffer {
    bool elf_ready = false;
    bool success = false;
    uint8_t* elf_buffer;
};

struct consoleLogBuffer {
    bool print_ready = false;
    String text;
};

struct crossCoreBuffers {
    sendELFApi send_elf_api;
    requestElfBuffer request_elf_file;
    elfBuffer recieve_buffer;
    consoleLogBuffer console_buffer;
};