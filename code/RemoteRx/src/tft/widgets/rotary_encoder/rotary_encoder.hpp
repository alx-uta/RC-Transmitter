/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include "../../../config/config.hpp"
#include <TFT_eSPI.h>

class RotaryEncoder {
 public:
    RotaryEncoder(
        Config& config, 
        TFT_eSPI& tft,
        int x,
        int y
    );

    int big_circle_radius = 30;
    int small_circle_radius = 5;

    void drawBigCircle();
    void drawSmallCircle(int x, int y, int state);
    void drawSmallCircles(
        int up,
        int down,
        int left,
        int right,
        int middle
    );
    void update(
        int up,
        int down,
        int left,
        int right,
        int middle
    );
    void init();

 private:
    Config& _config;
    TFT_eSPI& _tft;
    int _x;
    int _y;
    uint16_t _border_colour;
    uint16_t _fill_colour;
};

#endif  // ROTARY_ENCODER_HPP
