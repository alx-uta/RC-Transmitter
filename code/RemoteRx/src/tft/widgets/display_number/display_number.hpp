/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef DISPLAY_NUMBER_HPP
#define DISPLAY_NUMBER_HPP

#include "../../../config/config.hpp"
#include <TFT_eSPI.h>

class DisplayNumber {
 public:
    DisplayNumber(Config& config, TFT_eSPI& tft, int x, int y);
    int _x;
    int _y;
    int _old_value;
    bool _widget_created = false;
    void init();
    void update(int number);

 private:
    Config& _config;
    TFT_eSPI& _tft;
};

#endif  // DISPLAY_NUMBER_HPP
