#pragma once
#include <string>
#include "services.h"

class Application_Manager {
  public:
    Application_Manager(const Services& services);
    bool Start();
    bool Select_Application(std::string app_location);
    bool Quit_Application();
  
  private:
    bool Change_App(std::string app_location);

    std::string app_folder;
    std::string boot_app_location;
    std::string menu_app_location;
    
};