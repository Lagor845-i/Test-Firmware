#include "application_manager.h"


Application_Manager::Application_Manager(const Services& services) {
  app_folder = "/Apps/";
  boot_app_location = app_folder + "Boot.app";
  menu_app_location = app_folder + "Menu.app";
}

bool Application_Manager::Start() {
  this->Change_App(boot_app_location);
  return true;
}

bool Application_Manager::Change_App(std::string app_location) {
  return true;
}

bool Application_Manager::Select_Application(std::string app_location) {
  return true;
}

bool Application_Manager::Quit_Application() {
  this->Change_App(menu_app_location);
  return true;
}