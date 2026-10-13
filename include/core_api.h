/*

This file manages all of the api values for cross core communication
The queueItem struct at the bottom functions as a packet for whatever
data you want to send over to the other core. 

Since this system is using the other core to retrieve data and run in 
the background, you should be careful to request items before you need
them. This will keep down the latency in the application.

*/

//Debug
#define LOG 1

//Queues
#define SENTQUEUE 2 // This will only be sent to the core communication manager. 

//Display
#define DRAWLINE 15
#define DRAWRECT 16
#define FILLSCREEN 17
#define DISPLAYUPDATE 18

//File Manager
#define GETFILE 30
#define GETELFFILE 31
#define FILERETURN 32
#define ELFFILERETURN 33
#define INVALIDFILE 34


struct queueItem {
    uint8_t operation;
    void* data;
};