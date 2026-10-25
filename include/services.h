#pragma once

#include <Arduino.h>
#include <SD.h>

#include "os.h"

struct System {
  std::function<void(String)> systemLog;
  std::function<void(String)> appLog;
  std::function<void(String)> error;
  std::function<File(String)> getFile;
  std::function<Input()> getInput;
  std::function<int()> getDisplayWidth;
  std::function<int()> getDisplayHeight;
};