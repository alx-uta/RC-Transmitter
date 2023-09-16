/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "../../../config/config.hpp"
#include <TFT_eSPI.h>

class Switch {
 public:
    Switch(
        Config& config, 
        TFT_eSPI& tft,
        int x,
        int y,
        int index
    );
    Switch(
        Config& config, 
        TFT_eSPI& tft,
        int x,
        int y,
        int index,
        int width,
        int height,
        int spacing,
        bool display_off_box
    );

    void update(int state);
    void init();

    int _old_value = -1;
    int _widget_created = false;
    int display_off_box = false;

 private:
    Config& _config;
    TFT_eSPI& _tft;
    int _x;
    int _y;
    int _index;
    int _width;
    int _height;
    int _spacing;
    bool _display_off_box;
};

#endif  // SWITCH_HPP
