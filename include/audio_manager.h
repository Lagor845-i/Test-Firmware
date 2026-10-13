#pragma once
#include <arduino.h>

#include "services.h"

class Audio_Manager {
    public:
        Audio_Manager(System& system_services);
        void playTone(uint8_t frequency);
};