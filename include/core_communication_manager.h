#include <Arduino.h>

#include "core_api.h"
#include "services.h"
#include "os.h"


class Core_Communication_Manager {
    public:
        Core_Communication_Manager(System system_api);
        crossCoreBuffers* getBuffer();
        void checkInput();

    private:
        System _system_api;
        crossCoreBuffers* _cross_core_buffer;
        osApi* _os_api = nullptr;
        bool _recieved_api = false;
        bool _first = true;
};