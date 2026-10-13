#include "services.h"

#include <SD.h>
#include <SPI.h>
#include <string>
#include <Arduino.h>

#define MAX_ELF_FILES 32
#define FILENAME_SIZE 12

class File_System_Manager {
  public:
    File_System_Manager(System& system_services);

    File getFile(String file_loc);
    void getAppFiles(char apps[MAX_ELF_FILES][FILENAME_MAX]);
    bool fileExistsByName(String file_loc);
    bool fileExistsByFile(File file);

  private:
    bool sd_card_installed = false;
    System& _system_services;
};