/* MIT License - Copyright (c) 2019-2024 Francis Van Roie
   For full license information read the LICENSE file in the project folder */

#if defined(ARDUINO) 
#include <Arduino.h>
#include <Wire.h>
#include "i2c_backlight.h"

namespace dev {

I2cBacklight::I2cBacklight(uint8_t address)
    : _address(address), _brightness(16) // Default to full brightness
{}

bool I2cBacklight::init()
{
    // Check if Wire is already initialized by testing a transmission
    Wire.beginTransmission(_address);
    uint8_t error = Wire.endTransmission(false); // Don't stop, just check if bus is alive
    
    if (error == 4) {
        // Error code 4 means bus is not ready, Wire needs initialization
        Wire.begin(I2CBCKL_SDA, I2CBCKL_SCL);

    }
    
    // Test communication with backlight device
    Wire.beginTransmission(_address);
    if (Wire.endTransmission() == 0) {
        LOG_INFO(TAG_GUI, F("I2C Backlight initialized at address 0x%02X"), _address);
        update(_brightness); // Set initial brightness
        return true;
    } else {
        LOG_ERROR(TAG_GUI, F("Failed to initialize I2C Backlight at address 0x%02X"), _address);
        return false;
    }
}

void I2cBacklight::update(uint8_t brightness)
{
    _brightness = brightness;
    Wire.beginTransmission(_address);
    Wire.write(_brightness);
    Wire.endTransmission();
    LOG_VERBOSE(TAG_GUI, F("Backlight brightness set to %d"), _brightness);
}

uint8_t I2cBacklight::getBrightness() const
{
    return _brightness;
}

} // namespace dev

dev::I2cBacklight haspBacklight(0x40); // Default address, adjust as needed

#endif // ARDUINO
