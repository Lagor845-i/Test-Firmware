
//Shows current firmware version. PLEASE RAISE NUMBER IF CHANGING ELF API!!!
#define FIRMWARE_VERSION 1

//Where on the SD card the applications are stored
#define APP_FOLDER "/apps/"
#define BOOT_APP APP_FOLDER "Boot.app"
#define BOOT_MENU APP_FOLDER "Menu.app"

//Allows debugging over Serial
#define DEBUG true
#define DEBUG_RATE 115200

//Sets the screen height of the connected Display
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

//How much memory is dedicated to the running ELF
#define ELF_PSRAM_ALLOCATION_SIZE 1500000

#define MAXQUEUESIZE 25