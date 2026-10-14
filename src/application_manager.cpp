#include "application_manager.h"


Application_Manager::Application_Manager(QueueHandle_t* queue):_process_queue_out(*static_cast<QueueHandle_t*>(queue)) {
  _app_services = new App;
  _app_services->version = FIRMWARE_VERSION;
}

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
    }
  }
}

//I need to build something to keep variables alive until they are not needed anymore
bool Application_Manager::callApi(queueItem item) {
  return xQueueSend(_process_queue_out,&item,0);
}

bool Application_Manager::requestFile(String file_loc) {
  String* file_loc_temp = new String(file_loc);
  queueItem packet;
  packet.operation = GETELFFILE;
  packet.data = file_loc_temp;
  if (callApi(packet) == pdPASS) {
    return true;
  }
  delete file_loc_temp;
  return false;
}
//Used chatgpt on this function for assistance with the ELF loading.
bool Application_Manager::loadFile(File elf_file) {
  if (!elf_file) {
    elf_file.close();
    return false;
  }
  size_t elf_size = elf_file.size();
  vTaskDelay(pdMS_TO_TICKS(10));
  esp_elf_init(&current_app);
  void* p = heap_caps_malloc(ELF_PSRAM_ALLOCATION_SIZE, MALLOC_CAP_SPIRAM);
  _elf_buffer = reinterpret_cast<uint8_t *>(p);
  elf_file.read(_elf_buffer,elf_size);
  esp_elf_relocate(&current_app,_elf_buffer);

  //Sets the entry for the ELF application. Had to convert it in order for it to be able to plug into a void* function pointer
  void (*entry)(App*);
  entry = reinterpret_cast<void (*)(App *)>(esp_elf_find_symbol("this_app_main"));
  entry(_app_services);

  return true;
}

bool Application_Manager::selectApplication(String app_location) {
  return true;
}

bool Application_Manager::quitApplication() {
  _quit_app = true;
  return true;
}