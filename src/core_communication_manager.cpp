#include "services.h"
#include "core_communication_manager.h"

Core_Communication_Manager::Core_Communication_Manager(System system_api):_system_api(system_api) {

};

QueueHandle_t Core_Communication_Manager::createTunnel() {
    inorout = false;
    _process_queue_in = xQueueCreate(10,sizeof(queueItem));
    return _process_queue_in;
};

void Core_Communication_Manager::setTunnelOut(QueueHandle_t queue) {
    _process_queue_out = queue;
}

queueItem Core_Communication_Manager::readQueue() {
    queueItem item;
    xQueueReceive(_process_queue_in,&item,0);
    
    switch (item.operation) {
        case LOG:
            _system_api.systemLog(*static_cast<String*>(item.data));
            delete item.data;
            break;

        case SENTQUEUE:
            setTunnelOut(*static_cast<QueueHandle_t*>(item.data));
            break;
        
        case DRAWLINE:

            break;

        case DRAWRECT:

            break;
        
        case FILLSCREEN:

            break;

        case DISPLAYUPDATE:

            break;

        case GETFILE:

            break;

        case GETELFFILE:
            
            break;
    }
};

bool Core_Communication_Manager::writeQueue(queueItem item) {
    return xQueueSend(_process_queue_out,&item,0);
};