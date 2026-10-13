/* 

I used AI to make this page for me. 
I didnt want to have to write all of this out and honestly didnt know how some of it worked.

*/

#pragma once

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device {
  lgfx::Bus_SPI _bus;
  lgfx::Panel_ST7789 _panel;

public:
  LGFX() {
    auto bus_cfg = _bus.config();

    bus_cfg.spi_host = SPI2_HOST;
    bus_cfg.spi_mode = 0;
    bus_cfg.freq_write = 40000000;
    bus_cfg.freq_read = 16000000;
    bus_cfg.spi_3wire = false;
    bus_cfg.use_lock = true;
    bus_cfg.dma_channel = SPI_DMA_CH_AUTO;

    bus_cfg.pin_sclk = 46;
    bus_cfg.pin_mosi = 3;
    bus_cfg.pin_miso = -1;
    bus_cfg.pin_dc   = 45;

    _bus.config(bus_cfg);
    _panel.setBus(&_bus);

    auto panel_cfg = _panel.config();

    panel_cfg.pin_cs  = 0;
    panel_cfg.pin_rst = 1;
    panel_cfg.pin_busy = -1;

    panel_cfg.memory_width  = 240;
    panel_cfg.memory_height = 320;
    panel_cfg.panel_width   = 240;
    panel_cfg.panel_height  = 320;

    panel_cfg.offset_x = 0;
    panel_cfg.offset_y = 0;
    panel_cfg.offset_rotation = 0;
    panel_cfg.invert = true;
    panel_cfg.rgb_order = false;

    _panel.config(panel_cfg);
    setPanel(&_panel);
  }
};

extern LGFX lcd;