#pragma once

#include <functional>
#include <SD.h>

#include "config.h"

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

struct App {
    float version = FIRMWARE_VERSION;
    std::function<void(String)> appLog;
    std::function<Input()> getInput;
};