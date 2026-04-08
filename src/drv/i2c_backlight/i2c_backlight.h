/* MIT License - Copyright (c) 2019-2024 Francis Van Roie
   For full license information read the LICENSE file in the project folder */

#ifndef HASP_I2C_BACKLIGHT_DRIVER_H
#define HASP_I2C_BACKLIGHT_DRIVER_H

#ifdef ARDUINO
#include <Arduino.h>
#include "ArduinoLog.h"
#include "hasp_conf.h"
#include <Wire.h>

// Define custom I2C pins for backlight (optional)
// If not defined, Wire will use existing I2C bus or default pins
// #define I2CBCKL_SDA <pin_number>
// #define I2CBCKL_SCL <pin_number>

namespace dev {

class I2cBacklight {
  private:
    uint8_t _address;
    uint8_t _brightness;

  public:
    I2cBacklight(uint8_t address = 0x30); // Default I2C address, adjust as needed
    bool init();
    void update(uint8_t brightness);
    uint8_t getBrightness() const;
};

} // namespace dev

using dev::I2cBacklight;
extern dev::I2cBacklight haspBacklight;

#endif // ARDUINO

#endif // HASP_I2C_BACKLIGHT_DRIVER_H
