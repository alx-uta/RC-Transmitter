/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "rotary_encoder.hpp"

RotaryEncoder::RotaryEncoder(
    Config & config, 
    TFT_eSPI & tft,
    int x,
    int y
)
    :   _config(config),
        _tft(tft) {
            _x = x;
            _y = y;
        }

void RotaryEncoder::drawBigCircle() {
    _tft.drawCircle(_x, _y, RotaryEncoder::big_circle_radius, _config.TFT_ENCODER_BORDER_COLOUR);
}

void RotaryEncoder::drawSmallCircle(int x, int y, int state) {
    _border_colour = state ? _config.TFT_ENCODER_ACTIV_COLOUR : _config.TFT_ENCODER_BORDER_COLOUR;
    _fill_colour = state ? _config.TFT_ENCODER_ACTIV_COLOUR : _config.TFT_ENCODER_BORDER_COLOUR;

    _tft.drawCircle(x, y, RotaryEncoder::small_circle_radius, _border_colour);
    _tft.fillCircle(x, y, RotaryEncoder::small_circle_radius - 2, _fill_colour);
}

void RotaryEncoder::drawSmallCircles(
    int up,
    int down,
    int left,
    int right,
    int middle
) {
    drawSmallCircle(_x, _y - RotaryEncoder::big_circle_radius, up);
    drawSmallCircle(_x, _y + RotaryEncoder::big_circle_radius, down);
    drawSmallCircle(_x - RotaryEncoder::big_circle_radius, _y, left);
    drawSmallCircle(_x + RotaryEncoder::big_circle_radius, _y, right);
    drawSmallCircle(_x, _y, middle);
}

void RotaryEncoder::init(){
    RotaryEncoder::drawBigCircle();
    RotaryEncoder::update(
        0, 0, 0, 0, 0
    );
}

void RotaryEncoder::update(
        int up,
        int down,
        int left,
        int right,
        int middle
) {
    RotaryEncoder::drawSmallCircles(
        up,
        down,
        left,
        right,
        middle
    );
}