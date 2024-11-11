#pragma once

#define LGFX_USE_V1
#include <LovyanGFX.h>

#define TFT_WIDTH 800
#define TFT_HEIGHT 480

namespace esphome {
namespace hd_device {

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ST7789 _panel_instance;
  lgfx::Bus_SPI _bus_instance;
  lgfx::Light_PWM _light_instance;
  lgfx::Touch_GT911 _touch_instance;

public:
  LGFX(void);
};

}  // namespace hd_device
}  // namespace esphome
