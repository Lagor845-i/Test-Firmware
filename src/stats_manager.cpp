#include "stats_manager.h"

Stats_Manager::Stats_Manager(System& system_services) 
    : _system_services(system_services) {

}

void Stats_Manager::reportStats() {
    ESP.getFreeHeap();
    _system_services.systemLog("Current PSRAM used"+String(ESP.getPsramSize()-ESP.getFreePsram()));
}