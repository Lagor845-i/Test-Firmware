#pragma once

#include "services.h"

class Input_Manager {
    public:
        Input_Manager(System& system_services);
        Input sysGetInput();

    private:
        Input stuff;
        System _system_services;
};