/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef HORIZONTAL_SLIDER_HPP
#define HORIZONTAL_SLIDER_HPP

#include "../../../config/config.hpp"
#include <TFT_eSPI.h>

class HorizontalSlider {
 public:
    HorizontalSlider(
        Config& config,
        TFT_eSPI& tft,
        int x,
        int y,
        int start_value,
        int end_value,
        int width
    );
    int _x;
    int _y;
    int _default_value = 127;
    int _start_value;
    int _end_value;
    int _width;

    int _slider_width = 6;
    int _slider_height = 6;
    int _line_track_distance = 5;

    int _old_value;
    int _current_position = -1;
    bool _widget_created = false;

    void _update(int number, bool init);
    void update(int number, bool init);
    void update(int number);
    void init();

 private:
    Config& _config;
    TFT_eSPI& _tft;
};

#endif  // HORIZONTAL_SLIDER_HPP
