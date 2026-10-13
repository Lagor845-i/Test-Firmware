#pragma once

#include "services.h"

class Input_Manager {
    public:
        Input_Manager(System& system_services);
        void sysGetInput();
        Input appGetInput();

    private:
        Input stuff;
        System _system_services;
};