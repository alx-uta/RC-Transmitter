/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef BATTERY_ICON_HPP
#define BATTERY_ICON_HPP

#include "../../../config/config.hpp"
#include <TFT_eSPI.h>

class BatteryIcon {
 public:
    BatteryIcon(Config& config, TFT_eSPI& tft, int x, int y, int width);
    int _x;
    int _y;
    int _width;
    int _old_value;
    bool _widget_created = false;
    void init(int percentage);
    void init();
    void update(int percentage);

 private:
    Config& _config;
    TFT_eSPI& _tft;
};

#endif  // BATTERY_ICON_HPP
