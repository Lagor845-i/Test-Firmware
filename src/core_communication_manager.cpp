#include "core_communication_manager.h"

Core_Communication_Manager::Core_Communication_Manager(System system_api):_system_api(system_api) {
    _cross_core_buffer = new crossCoreBuffers{};
};

crossCoreBuffers* Core_Communication_Manager::getBuffer() {
    return _cross_core_buffer;
}

void Core_Communication_Manager::checkInput() {
    //Recieves the api for the currently running application
    if (_cross_core_buffer->send_elf_api.new_api == true) {
        _os_api = _cross_core_buffer->send_elf_api.os_api;
        _cross_core_buffer->send_elf_api.new_api = false;
        _system_api.systemLog("Recieved new App Api");
    }

    //Recieves requests from the application manager to get app files.
    if (_cross_core_buffer->request_elf_file.new_request == true) {
        File elf_file = _system_api.getFile(_cross_core_buffer->request_elf_file.file_name);
        uint8_t* file_buffer = static_cast<uint8_t*>(heap_caps_malloc(elf_file.size(), MALLOC_CAP_SPIRAM));
        if (!elf_file) {
            _system_api.systemLog("Invalid App Name");
            _cross_core_buffer->recieve_buffer.success = false;
        } else {
            _system_api.systemLog("Loading App...");
            elf_file.read(file_buffer, elf_file.size());
            _system_api.systemLog(String(elf_file.size()));
            _cross_core_buffer->recieve_buffer.elf_buffer = file_buffer;
            _cross_core_buffer->recieve_buffer.elf_ready = true;
            _cross_core_buffer->request_elf_file.new_request = false;
            _cross_core_buffer->recieve_buffer.success = true;
        }
    }

    if (_cross_core_buffer->console_buffer.print_ready == true) {
        _system_api.systemLog(_cross_core_buffer->console_buffer.text);
        _cross_core_buffer->console_buffer.print_ready = false;
    }

    if (_os_api != nullptr) {
        if (_os_api->log_queue.send_queue != nullptr) {
            while (uxQueueMessagesWaiting(_os_api->log_queue.send_queue) != 0) {
                _system_api.systemLog("Should print");
                std::string* text = nullptr;
                xQueueReceive(_os_api->log_queue.send_queue, &text, 0);
                _system_api.appLog(String(text->c_str()));
            }
        }
    }
}