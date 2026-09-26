#pragma once

#include <string>

struct Input {
  bool a;
  bool b;
  bool u;
  bool d;
  bool l;
  bool r;
  float jsx;
  float jsy;
};

struct Services {
  void (*get_display)();
  void (*read_file)(std::string file_location);
  void (*send_binary_over_wifi)(std::string ip_address, std::string msg);
  void (*retrieve_recieved_wifi_data)();
  Input (*get_input)();
};