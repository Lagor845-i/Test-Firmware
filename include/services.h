#pragma once

#include <Arduino.h>

#include "app_api.h"

struct System {
  std::function<void(String)> systemLog;
  std::function<void(String)> error;
  std::function<File(String)> getFile;
  std::function<void()> getInput;
};