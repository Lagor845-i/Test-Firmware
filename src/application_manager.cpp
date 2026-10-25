#include "application_manager.h"
<<<<<<< HEAD
=======

>>>>>>> 439d9c0b2dd8cab375a1649055402f47c6aa835c

extern "C" {
  void* os_api = nullptr;
}

<<<<<<< HEAD
Application_Manager::Application_Manager(crossCoreBuffers* buffers):_cross_core_buffers(buffers) {
  printToConsole("Starting Application Manager");
  _app_services = new osApi{};
  _app_services->version = FIRMWARE_VERSION;
  _app_services->recieve_wifi_ssids.recieve_queue = xQueueCreate(10,sizeof(std::string*));
  _app_services->send_tcp_over_wifi.send_queue = xQueueCreate(10,sizeof(std::string*));
  _app_services->request_download.send_queue = xQueueCreate(5,sizeof(std::string*));
  _app_services->log_queue.send_queue = xQueueCreate(10,sizeof(std::string*));
  os_api = _app_services;
  register_custom_elf_symbols();
}

void Application_Manager::Start() {
  sendAppApi();
  printToConsole("Sent App Api");
  requestELFFile(BOOT_APP);
  printToConsole("Requested ELF file: " + String(BOOT_APP));
  bool first = true;
  bool running = true;
  while (running) {
    if (first) {
      do {
        uint8_t* return_buffer = recieveElfFile();
        _elf_buffer = return_buffer;
        if (return_buffer == nullptr) {
          continue;
        } else {
          printToConsole("Attempting to boot app");
          if (bootFile(_elf_buffer)) {
            printToConsole("Boot successful");
          } else {
            printToConsole("Boot Failed!!!");
          }
          break;
        }
      } while (true);
      first = false;
=======
bool Application_Manager::Start() {
  bool running = true;
  while (running) {
    vTaskDelay(pdMS_TO_TICKS(10));
    queueItem* item;
    xQueueReceive(_process_queue_in,&item,0);
    switch (item->operation) {
      case LOG:

        
        break;
    }
    File elf_file;
    while (true) {
      if (this->requestFile(boot_app_location)) {
        queueItem temp;
        xQueueReceive(_process_queue_in,&temp,0);
        break;
      }
>>>>>>> 439d9c0b2dd8cab375a1649055402f47c6aa835c
    }
  }
}

bool Application_Manager::sendAppApi() {
  _cross_core_buffers->send_elf_api.os_api = _app_services;
  _cross_core_buffers->send_elf_api.new_api = true;
  return true;
}

bool Application_Manager::printToConsole(String text) {
  if (_cross_core_buffers->console_buffer.print_ready == false) {
    _cross_core_buffers->console_buffer.text = text;
    _cross_core_buffers->console_buffer.print_ready = true;
    return true;
  } return false;
}

bool Application_Manager::isElf(File file) {
  if (String(file.name()).endsWith(".app")) {return true;}
  return false;
}

bool Application_Manager::requestELFFile(String file_name) {
  String temp = String(APP_FOLDER + file_name);
  _cross_core_buffers->request_elf_file.file_name = temp;
  _cross_core_buffers->request_elf_file.new_request = true;
  return true;
}

uint8_t* Application_Manager::recieveElfFile() {
  if (_cross_core_buffers->recieve_buffer.elf_ready) {
    _cross_core_buffers->recieve_buffer.elf_ready = false;
    return _cross_core_buffers->recieve_buffer.elf_buffer;
  }
  return nullptr;
}

//Used chatgpt on this function for assistance with the ELF loading.
bool Application_Manager::bootFile(uint8_t* file_bytes) {
  esp_elf_init(&current_app);

  if (esp_elf_relocate(&current_app,file_bytes) != ESP_OK) {
    printToConsole("Invalid Elf Configuration");
    return false;
  }

  //Sets the entry for the ELF application. Had to convert it in order for it to be able to plug into a void* function pointer
  if (esp_elf_request(&current_app,0,0,nullptr)) {
    printToConsole("Failed to Boot ELF");
    return false;
  }
  return true;
}

bool Application_Manager::quitApplication() {
<<<<<<< HEAD
  esp_elf_deinit(&current_app);
  heap_caps_free(_elf_buffer);
=======
  _quit_app = true;
>>>>>>> 439d9c0b2dd8cab375a1649055402f47c6aa835c
  return true;
}