#pragma once

#include <Arduino.h>
#include <SD.h>

#include "os.h"

struct System {
  //Debug functions
  std::function<void(String)> systemLog; //
  std::function<void(String)> appLog; //
  std::function<void(String)> error; 
  std::function<bool()> getDebugOn;
  std::function<void(bool on_off)> setDebug;
  std::function<void(int baud_rate)> setDebugBaudRate;

  //File Manager function
  std::function<File(String)> getFile; //
  std::function<int()> sdCardSize;
  std::function<int()> sdCardFree;

  //IO functions
  std::function<Input()> getInput; //
  std::function<void(uint8_t[23][3])> setAleds;
  std::function<void(uint8_t,uint8_t)> setAled;

  //Display functions
  std::function<int()> getDisplayWidth;
  std::function<int()> getDisplayHeight;
  std::function<void(LGFX_Sprite*)> setDisplayBuffer; //
  std::function<void()> updateDisplay; //

  //Wifi functions
  std::function<SSIDS()> getWifiSSIDS;

  std::function<bool()> wifiConnected;
  std::function<std::string()> getWifiSSID;
  std::function<std::string()> getIpAddress;
  std::function<int()> getWifiSignalStrength;

  std::function<void(std::string,int)> connectToWifi;
  std::function<bool(std::string,std::string)> setBackgroundDownload;

  //System Health
  std::function<int()> getTotalMemory;
  std::function<int()> getMemoryUsed;
};