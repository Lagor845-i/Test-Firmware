#include "os.h"

os::os(osApi* api) : _os_api(api) {

};

float os::getOSAPIVersion() {
    return _os_api->version;
}

void os::startApp(std::string app_name) {
    _os_api->start_app.app_name = app_name;
    _os_api->start_app.request = true;
}

void os::quitApp() {
    _os_api->quit_app.request = true;
}

//Debug Functions

bool os::log(std::string text) {
    std::string* temp_text = new std::string(text);
    if (xQueueSend(_os_api->log_queue.send_queue, &temp_text, 0) == pdTRUE) {
        return true;
    } return false;
}

bool os::toggleDebug() {
    if (_os_api->debug_toggle.debug_on) {
        _os_api->debug_toggle.debug_on = false;
        return false;
    }
    _os_api->debug_toggle.debug_on = true;
    return true;
}

/*
Returns a bool showing if serial debug is on or off

true = On
false = Off
*/
bool os::debugState() {
    return _os_api->debug_toggle.debug_on;
}

void os::setdebugBaudRate(int baud) {
    _os_api->debug_baud_rate.rate = baud;
    _os_api->debug_baud_rate.request = true;
}

/*
Get the SSID of currently connected wifi network

Returns a blank string when not connected to a wifi network.
*/
std::string os::getCurrentWifiNetwork() {
    if (_os_api->current_wifi_network.connected) {
        return _os_api->current_wifi_network.wifi_ssid;
    } return "";
}

/*
Connects you to the wifi network input.

To check if the connection was successful use the 
getCurrentWifiNetwork() function.
*/
void os::connectToWifi(std::string SSID,std::string password) {
    _os_api->connect_to_network.wifi_ssid = SSID;
    _os_api->connect_to_network.wifi_password = password;
    _os_api->connect_to_network.request = true;
}

SSIDS os::getSSIDS() {
    _os_api->get_wifi_ssids.request = true;
    
    while (!_os_api->recieve_wifi_ssids.ready) {
        
    }
    SSIDS data;
    data.amount = 0;
    while (uxQueueMessagesWaiting(_os_api->recieve_wifi_ssids.recieve_queue) != 0) {
        std::string* text = nullptr;
        xQueueReceive(_os_api->recieve_wifi_ssids.recieve_queue,text,0);
        data.ssids[data.amount] = text;
        data.amount ++;
    }
    return data;
}

/*
Sends a request to download an item in the background.
This works without needing to be using the current app.
You can queue up to 5 downloads at a time

Output
0 = Queue is full
1 = Successfully queued
2 = Not connected to wifi
*/
uint8_t os::downloadFromLink(std::string link) {
    std::string* text = new std::string(link);
    if (_os_api->current_wifi_network.connected) {
        if (xQueueSend(_os_api->request_download.send_queue,text,0) == pdTRUE) {
            return 1;
        } return 0;
    } return 2;
    
}


//Display Commands
/*
Takes a display buffer

Sends display buffer to the display when you call the 
updateDisplay() function
*/
void os::setDisplayBuffer(LGFX_Sprite* display_buffer) {
    _os_api->display_buffer.display_buffer = display_buffer;
    _os_api->display_buffer.request = true;
}

/*
Updates the display from the buffer given 
using the setDisplayBuffer() functon
*/
void os::updateDisplay() {
    _os_api->display_update.request = true;
}

/*
Requires you to input an array of two ints
An example is: int this_array[2];

this_array[0] would be the display width
this_array[1] would be the display height
*/
void os::getDisplayInfo(int data[2]) {
    data[0] = _os_api->display_info.display_width;
    data[1] = _os_api->display_info.display_height;
}

//IO Commands
/*
Gets system input from buttons, joystick, and accelerometer
*/
Input os::getInput() {
    return _os_api->read_io.input;
}

void os::setALEDS(uint8_t color[23][3]) {
    for (int i = 0; i < 3; i++) {
        _os_api->set_aleds.leds_colors[i][0] = color[i][0];
        _os_api->set_aleds.leds_colors[i][1] = color[i][1];
        _os_api->set_aleds.leds_colors[i][2] = color[i][2];
    }
    _os_api->set_aleds.request = true;
}

void os::setALED(uint8_t led_num, uint8_t color[3]) {
    _os_api->set_aled.led_num = led_num;
    _os_api->set_aled.color[0] = color[0];
    _os_api->set_aled.color[1] = color[1];
    _os_api->set_aled.color[2] = color[2];
    _os_api->set_aled.request = true;
}