#pragma once

#include <string.h>
#include <LovyanGFX.hpp>

#define EBADGE_WIFI_ON 1
#define EBADGE_WIFI_OFF 0

#define DOWNLOAD_QUEUE_FULL 0
#define SUCCESSFULLY_QUEUED_DOWNLOAD 1
#define NOT_CONNECTED_TO_WIFI 2

//Data Types

struct Input {
    int a;
    int b;
    int u;
    int d;
    int l;
    int r;
    float jsx;
    float jsy;
    float accel_x;
    float accel_y;
    float accel_z;
};

struct SSIDS {
    std::string* ssids[10];
    int amount;
};

struct packet {
    std::string Ip_address = "";
    int port;
};

//Commands
//App Switching Commands

struct startApp {
    bool request = false;
    std::string app_name = "";
};

struct quitApp {
    bool request = false;
};

//Wifi Commands

struct requestWifiOnOff {
    bool request = true;
};

struct currentWifiNetwork {
    bool connected = false;
    std::string wifi_ssid = "";
    int signal_strength = 0;
    std::string Ip_address;
};

struct connectToNetwork {
    bool request = false;
    std::string wifi_ssid = "";
    std::string wifi_password = "";
};

struct getWifiSSIDs {
    bool request = false;
};

struct recieveWifiSSIDs {
    bool ready = false;
    QueueHandle_t recieve_queue;
};

struct sendTCPOverWifi {
    QueueHandle_t send_queue;
};

struct requestDownload {
    QueueHandle_t send_queue;
};

//Debug Commands

struct logQueue {
    QueueHandle_t send_queue;
};

struct debugToggle {
    bool debug_on = false;
};

struct debugBAUDRate {
    int rate = 115200;
    bool request = false;
};

//Display Commands

struct displayInfo {
    int display_width;
    int display_height;
};

struct displayBuffer {
    bool request = false;
    LGFX_Sprite* display_buffer;
};

struct displayUpdate {
    bool request = false;
};

//Input Commands

struct readIO {
    Input input;
};

struct setALEDS {
    bool request = false;
    uint8_t leds_colors[23][3];
};

struct setALED {
    bool request = false;
    uint8_t led_num;
    uint8_t color[3];
};

struct osApi {
    float version = 1.0;
    //App switching Commands
    startApp start_app;
    quitApp quit_app;

    //Wifi Commands
    currentWifiNetwork current_wifi_network;
    connectToNetwork connect_to_network;
    getWifiSSIDs get_wifi_ssids;
    sendTCPOverWifi send_tcp_over_wifi;
    recieveWifiSSIDs recieve_wifi_ssids;
    requestDownload request_download;
    requestWifiOnOff turn_off_wifi;

    //Debug Commands
    logQueue log_queue;
    debugToggle debug_toggle;
    debugBAUDRate debug_baud_rate;

    //Display Commands
    displayInfo display_info;
    displayBuffer display_buffer;
    displayUpdate display_update;

    //IO Commands
    readIO read_io;
    setALEDS set_aleds;
    setALED set_aled;
};

class os {
    public:
        os(osApi* api);
        float getOSAPIVersion();

        //Switching App Commands

        void startApp(std::string app_name);
        void quitApp();

        //Wifi Commands

        std::string getCurrentWifiNetwork();
        void connectToWifi(std::string SSID, std::string password);
        void sendTCPData(std::string ip_address,int port);
        SSIDS getSSIDS();
        uint8_t downloadFromLink(std::string link);

        //Debug Commands

        bool toggleDebug();
        bool debugState();
        void setdebugBaudRate(int baud);
        bool log(std::string text);

        //Display Commands

        void getDisplayInfo(int data[2]);
        void setDisplayBuffer(LGFX_Sprite* display_buffer);
        void updateDisplay();
        void sendNotification(std::string text);

        //IO Commands

        Input getInput();
        
        void setALEDS(uint8_t color[23][3]);
        void setALED(uint8_t led_num,uint8_t color[3]);

        void getSDCardInfo();
    
    private:
        osApi* _os_api;
};