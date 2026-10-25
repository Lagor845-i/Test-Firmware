#include "debug_manager.h"

Debug_Manager::Debug_Manager() {
    
};

void Debug_Manager::begin(unsigned long serial_speed) {
    Serial.begin(serial_speed);
}

void Debug_Manager::stop() {
    _on = false;
    Serial.println("[System] Debug ending");
    Serial.end();
}

void Debug_Manager::set(bool debug_value) {
    _on = debug_value;
    if (_on) {
        Serial.println("[System] Debug on");
    } else {
        Serial.println("[System] Debug off");
    }
}

void Debug_Manager::systemLog(String msg) {
    if (_on) {
        Serial.println("[System] " + msg);
    }
};

void Debug_Manager::applicationLog(String msg) {
    Serial.println("[Application] "+msg);
};