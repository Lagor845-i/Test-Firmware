#include <Arduino.h>

#include "core_api.h"


class Core_Communication_Manager {
    public:
        Core_Communication_Manager(System system_api);

        //Creation and adding of tunnels
        QueueHandle_t createTunnel();
        void setTunnelOut(QueueHandle_t queue);

        //Communication through tunnels
        queueItem readQueue();
        bool writeQueue(queueItem item);

    private:
        QueueHandle_t _process_queue_in;
        QueueHandle_t _process_queue_out;
        bool inorout;
        System _system_api;
};