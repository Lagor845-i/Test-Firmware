#include <Arduino.h>

#include "services.h"

class Stats_Manager {
    public:
        Stats_Manager(System& system_services);
        void reportStats();
        void displayStats();

    private:
        System& _system_services;
};