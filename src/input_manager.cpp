#include "input_manager.h"

#include <Wire.h>
#include <Arduino.h>

#define ACCEL_ADDR 0x1C
#define SDA_PIN 41
#define SCL_PIN 42

#define x_reg 0x01
#define y_reg 0x03
#define z_reg 0x05

#define JOYSTICK_X_PIN 8
#define JOYSTICK_Y_PIN 9

#define A_BUTTON 34
#define B_BUTTON 33

#define U_BUTTON 11
#define D_BUTTON 47
#define L_BUTTON 21
#define R_BUTTON 10

Input_Manager::Input_Manager(System& system_services) {
    _system_services = system_services;
    pinMode(A_BUTTON,INPUT);
    pinMode(B_BUTTON,INPUT);
    pinMode(U_BUTTON,INPUT);
    pinMode(D_BUTTON,INPUT);
    pinMode(L_BUTTON,INPUT);
    pinMode(R_BUTTON,INPUT);
    pinMode(JOYSTICK_X_PIN,INPUT);
    pinMode(JOYSTICK_Y_PIN,INPUT);
    _system_services.systemLog("Inputs Initialized");
    
    //Attempts to initialize the accelerometer.
    /*
    uint8_t data;
    Wire.begin(SDA_PIN,SCL_PIN,400000);
    Wire.beginTransmission(ACCEL_ADDR);
    Wire.write(0x0D);
    Wire.endTransmission(true);
    Wire.requestFrom(ACCEL_ADDR,uint8_t(1));
    data = Wire.read();
    _system_services.systemLog(String(data));*/
};

Input Input_Manager::sysGetInput() {
    stuff.a = digitalRead(A_BUTTON);
    stuff.b = digitalRead(B_BUTTON);
    stuff.u = digitalRead(U_BUTTON);
    stuff.d = digitalRead(D_BUTTON);
    stuff.l = digitalRead(L_BUTTON);
    stuff.r = digitalRead(R_BUTTON);
    stuff.jsx = analogRead(JOYSTICK_X_PIN);
    stuff.jsy = analogRead(JOYSTICK_Y_PIN);
    return stuff;
}