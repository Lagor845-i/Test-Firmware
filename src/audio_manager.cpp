#include "audio_manager.h"

#define BUZZER 48

Audio_Manager::Audio_Manager(System& system_services) {
    tone(BUZZER,500);
    vTaskDelay(100);
    tone(BUZZER,750);
    vTaskDelay(100);
    tone(BUZZER,1000);
};

void Audio_Manager::playTone(uint8_t frequency) {
    tone(BUZZER,frequency);
};