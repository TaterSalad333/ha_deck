#include "LGFX.h"

namespace esphome {
namespace hd_device {

LGFX::LGFX(void)
{
  {
    auto cfg = _bus_instance.config();
    cfg.freq_write = 20000000;        // SPI frequency
    cfg.pin_sclk = 13;                // SPI clock pin
    cfg.pin_mosi = 11;                // SPI MOSI pin
    cfg.pin_dc = 10;                  // SPI DC pin
    cfg.pin_rst = 4;                  // Reset pin
    cfg.pin_cs = 5;                   // Chip Select pin (if applicable)

    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);
  }

  {
    auto cfg = _panel_instance.config();

    cfg.pin_cs = 5;                   // Chip select pin
    cfg.pin_rst = 4;                  // Reset pin
    cfg.pin_busy = -1;                // No busy pin

    cfg.panel_width = TFT_WIDTH;      // Set width
    cfg.panel_height = TFT_HEIGHT;    // Set height
    cfg.offset_x = 0;                 // No offset
    cfg.offset_y = 0;                 // No offset
    cfg.offset_rotation = 0;          // Rotation offset
    cfg.dummy_read_pixel = 8;         // Dummy read pixel
    cfg.dummy_read_bits = 1;          // Dummy read bits
    cfg.readable = true;              // Enable readable
    cfg.invert = true;                // Invert colors if needed
    cfg.rgb_order = false;            // RGB order
    cfg.dlen_16bit = false;           // 16-bit data length
    cfg.bus_shared = true;            // Bus sharing enabled

    _panel_instance.config(cfg);
  }

  {
    auto cfg = _light_instance.config();

    cfg.pin_bl = 45;                  // Backlight pin
    cfg.invert = false;               // Backlight inversion
    cfg.freq = 44100;                 // PWM frequency
    cfg.pwm_channel = 7;              // PWM channel

    _light_instance.config(cfg);
    _panel_instance.setLight(&_light_instance);
  }

  {
    auto cfg = _touch_instance.config();

    cfg.x_min = 0;                    // Touchscreen min x
    cfg.x_max = 799;                  /
