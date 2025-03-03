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
    cfg.pin_dc = 10;                  // Data/Command pin
    cfg.pin_rst = 4;                  // Reset pin
    cfg.pin_cs = 5;                   // Chip Select pin

    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);
  }

  {
    auto cfg = _panel_instance.config();
    cfg.pin_cs = 5;                   // Chip select pin
    cfg.pin_rst = 4;                  // Reset pin
    cfg.pin_busy = -1;                // No busy pin (if unused)

    cfg.panel_width = TFT_WIDTH;      // Panel width
    cfg.panel_height = TFT_HEIGHT;    // Panel height
    cfg.offset_x = 0;                 // Offset for X axis
    cfg.offset_y = 0;                 // Offset for Y axis
    cfg.invert = true;                // Invert colors (optional)
    cfg.rgb_order = false;            // RGB order (depends on your display)
    cfg.dlen_16bit = false;           // Data length 16-bit or 8-bit (depending on your panel)

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
    cfg.x_max = 799;                  // Touchscreen max x
    cfg.y_min = 0;                    // Touchscreen min y
    cfg.y_max = 479;                  // Touchscreen max y
    cfg.pin_int = 7;                  // Touch interrupt pin
    cfg.bus_shared = true;            // Bus sharing enabled
    cfg.offset_rotation = 0;          // Rotation offset

    cfg.i2c_port = 1;                 // I2C port
    cfg.i2c_addr = 0x38;              // Touch I2C address
    cfg.pin_sda = 6;                  // SDA pin
    cfg.pin_scl = 5;                  // SCL pin
    cfg.freq = 400000;                // I2C frequency

    _touch_instance.config(cfg);
    _panel_instance.setTouch(&_touch_instance);
  }

  setPanel(&_panel_instance);         // Set the panel instance
}

}  // namespace hd_device
}  // namespace esphome
