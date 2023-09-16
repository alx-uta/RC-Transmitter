/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef VERTICAL_SLIDER_HPP
#define VERTICAL_SLIDER_HPP

#include "../../../config/config.hpp"
#include <TFT_eSPI.h>

class VerticalSlider {
 public:
    VerticalSlider(
        Config& config,
        TFT_eSPI& tft,
        int x,
        int y,
        int start_value,
        int end_value,
        int height,
        int margin_top,
        int track_width,
        int track_spacing
    );
    int _x;
    int _y;
    int _default_value = 127;
    int _start_value;
    int _end_value;
    int _height;
    int _margin_top;
    int _track_width;
    int _track_spacing;

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

#endif  // VERTICAL_SLIDER_HPP
