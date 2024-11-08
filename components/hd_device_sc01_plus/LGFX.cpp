#include "LGFX.h"

namespace esphome {
namespace hd_device {

LGFX::LGFX(void)
{
  // Configure the LCD panel bus
  {
    auto cfg = _bus_instance.config();
    cfg.freq_write = 20000000;      // ST7789V typically supports 20MHz SPI
    cfg.pin_wr = 47;
    cfg.pin_rd = -1;
    cfg.pin_rs = 0;

    // Define LCD data interface for 8-bit MCU parallel
    cfg.pin_d0 = 9;
    cfg.pin_d1 = 46;
    cfg.pin_d2 = 3;
    cfg.pin_d3 = 8;
    cfg.pin_d4 = 18;
    cfg.pin_d5 = 17;
    cfg.pin_d6 = 16;
    cfg.pin_d7 = 15;

    _bus_instance.config(cfg);       // Apply the configuration
    _panel_instance.setBus(&_bus_instance);
  }

  // Configure the panel settings specific to ST7789V
  {
    auto cfg = _panel_instance.config();

    cfg.pin_cs = -1;                 // Chip select pin (set to -1 if not used)
    cfg.pin_rst = 4;                 // Reset pin
    cfg.pin_busy = -1;               // Busy pin (if available, -1 if not used)

    cfg.panel_width = 240;           // ST7789V width
    cfg.panel_height = 320;          // ST7789V height
    cfg.offset_x = 0;                // Offset for ST7789V
    cfg.offset_y = 0;
    cfg.offset_rotation = 0;         // Adjust if needed based on orientation
    cfg.dummy_read_pixel = 8;
    cfg.dummy_read_bits = 1;
    cfg.readable = false;            // ST7789V generally doesn’t support reading
    cfg.invert = false;              // Set to true if colors are inverted
    cfg.rgb_order = false;           // False for ST7789V RGB order
    cfg.dlen_16bit = false;          // False for 8-bit mode
    cfg.bus_shared = true;

    _panel_instance.config(cfg);     // Apply panel configuration
  }

  // Configure the backlight
  {
    auto cfg = _light_instance.config();

    cfg.pin_bl = 45;                 // Backlight pin
    cfg.invert = false;              // Adjust if backlight is inverted
    cfg.freq = 44100;                // PWM frequency for backlight
    cfg.pwm_channel = 7;

    _light_instance.config(cfg);      // Apply backlight configuration
    _panel_instance.setLight(&_light_instance);
  }

  // Configure the GT911 touch controller
  {
    auto cfg = _touch_instance.config();

    cfg.x_min = 0;
    cfg.x_max = 239;                 // Max X for 240x320 resolution
    cfg.y_min = 0;
    cfg.y_max = 319;                 // Max Y for 240x320 resolution
    cfg.pin_int = 7;                 // Interrupt pin for GT911
    cfg.bus_shared = true;
    cfg.offset_rotation = 0;         // Adjust if touch orientation needs to be rotated

    cfg.i2c_port = 1;                // I²C port, check if correct for your setup
    cfg.i2c_addr = 0x38;             // GT911 default I²C address
    cfg.pin_sda = 6;                 // I²C SDA pin
    cfg.pin_scl = 5;                 // I²C SCL pin
    cfg.freq = 400000;               // I²C frequency for GT911

    _touch_instance.config(cfg);      // Apply touch configuration
    _panel_instance.setTouch(&_touch_instance);
  }
  
  setPanel(&_panel_instance);         // Set the configured panel
}

}  // namespace hd_device
}  // namespace esphome
