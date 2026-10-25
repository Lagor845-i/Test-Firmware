#include "os.h"

os::os(osApi* api) : _os_api(api) {

};

//Debug Functions
void os::log(std::string text) {
    std::string* temp_text = new std::string(text);
    xQueueSend(_os_api->log_queue.send_queue, temp_text, 0);
}