#include <Arduino.h>
#include <freertos/queue.h>

#define DEBUG_ON true
#define DEBUG_OFF false

class Debug_Manager {
    public:
        Debug_Manager();
        void begin(unsigned long serial_speed);
        void stop();
        void set(bool debug_value);
        void systemLog(String msg);
        void applicationLog(String msg);
    
    private:
        bool _on = false;
};