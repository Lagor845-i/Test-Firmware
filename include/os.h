#pragma once

#include <string.h>
#include <LovyanGFX.hpp>

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

//App Switching Commands
struct startApp {
    bool request = false;
    std::string app_name = "";
};

struct quitApp {
    bool request = false;
};

//Wifi Commands
struct currentWifiNetwork {
    bool connected = false;
    std::string wifi_ssid = "";
    int signal_strength = 0;
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

//Display Commands
struct displayBuffer {
    bool request = false;
    LGFX_Sprite* display_buffer;
};

//Input Commands 
struct readIO {
    Input input;
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

    //Debug Commands
    logQueue log_queue;

    //Display Commands
    displayBuffer display_buffer;

    //Input Commands
    readIO read_io;
};

class os {
    public:
        os(osApi* api);
        float getOSAPIVersion();

        //Switching App Commands
        void startApp();
        void quitApp();

        //Wifi Commands
        std::string getCurrentWifiNetwork();
        void connectToWifi(std::string SSID, std::string password);
        void sendData(std::string ip_address,int port);
        void getSSIDS();
        void downloadFromLink(std::string link);

        //Debug Commands
        void log(std::string text);

        //Display Commands
        void setDisplay(LGFX_Sprite* display_buffer);

        //Input Commands
        Input getInput();
    
    private:
        osApi* _os_api;
};