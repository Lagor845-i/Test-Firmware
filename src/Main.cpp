#include "services.h"
#include "managers.h"
#include "config.h"

Led_Manager* led_manager;
Wifi_Manager* wifi_manager;
Input_Manager* input_manager;
Stats_Manager* stats_manager;
Audio_Manager* audio_manager;
Display_Manager* display_manager;
Bluetooth_Manager* bluetooth_manager;
File_System_Manager* file_system_manager;
Application_Manager* application_manager;
Core_Communication_Manager* core_communication_manager;

void startcore1(void* queue) {
  QueueHandle_t* queue_actually = static_cast<QueueHandle_t*>(queue);
  application_manager = new Application_Manager(queue_actually);
  application_manager->Start();
}

void setup() {
  // put your setup code here, to run once:
  
  System system_services;

  Debug_Manager debug_manager = Debug_Manager();
  debug_manager.begin(DEBUG_RATE);
  if (DEBUG == true) {
    debug_manager.set(DEBUG_ON);
  }
  system_services.systemLog = [&debug_manager](String message) {debug_manager.systemLog(message);};
  debug_manager.systemLog("Psram Size "+String(ESP.getPsramSize()));
  led_manager = new Led_Manager(system_services);
  wifi_manager = new Wifi_Manager(system_services);
  input_manager = new Input_Manager(system_services);
  system_services.getInput = []() -> void {return input_manager->sysGetInput();};
  stats_manager = new Stats_Manager(system_services);
  display_manager = new Display_Manager(system_services,SCREEN_HEIGHT,SCREEN_WIDTH);
  display_manager->begin();
  vTaskDelay(pdMS_TO_TICKS(1));
  system_services.error = [](String error) -> void {return display_manager->error(error);};
  bluetooth_manager = new Bluetooth_Manager(system_services);
  file_system_manager = new File_System_Manager(system_services);
  system_services.getFile = [](String file) -> File {return file_system_manager->getFile(file);};
  core_communication_manager = new Core_Communication_Manager(system_services);
  QueueHandle_t queue = core_communication_manager->createTunnel();
  led_manager->begin();
  xTaskCreatePinnedToCore(startcore1,"Core1Watch",4096,queue,3,nullptr,1);
}

void loop() {
  vTaskDelay(3);
}