#include "input_manager.h"
#include "Arduino.h"

#define JOYSTICK_X_PIN 8
#define JOYSTICK_Y_PIN 9

#define A_BUTTON 34
#define B_BUTTON 33

#define U_BUTTON 11
#define D_BUTTON 47
#define L_BUTTON 21
#define R_BUTTON 10

Input_Manager::Input_Manager() {
    pinMode(A_BUTTON,INPUT);
    pinMode(B_BUTTON,INPUT);
    pinMode(U_BUTTON,INPUT);
    pinMode(D_BUTTON,INPUT);
    pinMode(L_BUTTON,INPUT);
    pinMode(R_BUTTON,INPUT);
};