#include "services.h"
#include "managers.h"
#include "config.h"
#include "core_api.h"

System system_services;
Debug_Manager* debug_manager;
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

void startcore1(void* crosscorebuffer) {
  application_manager = new Application_Manager(static_cast<crossCoreBuffers*>(crosscorebuffer));
  application_manager->Start();
}

void setup() {
  // put your setup code here, to run once:
  debug_manager = new Debug_Manager();
  debug_manager->begin(DEBUG_RATE);
  if (DEBUG == true) {
    debug_manager->set(DEBUG_ON);
  }
  system_services.systemLog = [](String message) {debug_manager->systemLog(message);};
  system_services.appLog = [](String message) {debug_manager->applicationLog(message);};
  debug_manager->systemLog("PSRAM DETECTED with a total of "+String(ESP.getPsramSize())+" bytes");

  led_manager = new Led_Manager(system_services);
  system_services.systemLog("Led Manager Initialized");
  vTaskDelay(pdMS_TO_TICKS(1)); //This is to avoid watchdog error.

  wifi_manager = new Wifi_Manager(system_services);
  system_services.systemLog("WIFI Manager Initialized");
  vTaskDelay(pdMS_TO_TICKS(1)); //This is to avoid watchdog error.

  input_manager = new Input_Manager(system_services);
  system_services.systemLog("Input Manager Initialized");
  system_services.getInput = []() -> Input {return input_manager->sysGetInput();};
  vTaskDelay(pdMS_TO_TICKS(1)); //This is to avoid watchdog error.

  stats_manager = new Stats_Manager(system_services);
  system_services.systemLog("Stats Manager Initialized");
  vTaskDelay(pdMS_TO_TICKS(1)); //This is to avoid watchdog error.

  display_manager = new Display_Manager(system_services,SCREEN_HEIGHT,SCREEN_WIDTH);
  system_services.systemLog("Display Manager Initialized");
  vTaskDelay(pdMS_TO_TICKS(1)); //This is to avoid watchdog error.
  display_manager->begin();
  system_services.getDisplayWidth = []() -> int {return display_manager->getDisplayWidth();};
  system_services.getDisplayHeight = []() -> int {return display_manager->getDisplayHeight();};
  system_services.error = [](String error) -> void {return display_manager->error(error);};

  bluetooth_manager = new Bluetooth_Manager(system_services);
  system_services.systemLog("Bluetooth Manager Initialized");
  vTaskDelay(pdMS_TO_TICKS(1)); //This is to avoid watchdog error.

  file_system_manager = new File_System_Manager(system_services);
  system_services.systemLog("File System Manager Initialized");
  system_services.getFile = [](String file) -> File {return file_system_manager->getFile(file);};
  vTaskDelay(pdMS_TO_TICKS(1)); //This is to avoid watchdog error

  core_communication_manager = new Core_Communication_Manager(system_services);
  system_services.systemLog("Core Communication Manager Initialized");
  led_manager->begin();
  xTaskCreatePinnedToCore(startcore1,"Core1Watch",4096,core_communication_manager->getBuffer(),3,nullptr,1);
}

void loop() {
  vTaskDelay(4);
  core_communication_manager->checkInput();
}