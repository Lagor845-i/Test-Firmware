#include "services.h"
#include "led_manager.h"
#include "wifi_manager.h"
#include "display_manager.h"
#include "bluetooth_manager.h"
#include "file_system_manager.h"
#include "application_manager.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Services services;
  Led_Manager led_manager = Led_Manager();
  Wifi_Manager wifi_manager = Wifi_Manager();
  Display_Manager display_manager = Display_Manager(240,320);
  Bluetooth_Manager bluetooth_manager = Bluetooth_Manager();
  File_System_Manager file_system_manager = File_System_Manager();
  Application_Manager application_manager = Application_Manager(services);
  led_manager.begin();
  display_manager.begin();
  application_manager.Start();
  Serial.println("Started");
}

void loop() {

}