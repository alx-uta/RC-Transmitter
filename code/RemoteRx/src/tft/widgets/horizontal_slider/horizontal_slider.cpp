/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "horizontal_slider.hpp"

HorizontalSlider::HorizontalSlider(
    Config & config, 
    TFT_eSPI & tft,
    int x,
    int y,
    int start_value,
    int end_value,
    int width
)
    :   _config(config),
        _tft(tft) {
            _x = x;
            _y = y;
            _start_value = start_value;
            _end_value = end_value;
            _width = width;
        }

void HorizontalSlider::init() {
    HorizontalSlider::update(-1, true);
}

void HorizontalSlider::update(int position) {
    HorizontalSlider::_update(position, false);
}
void HorizontalSlider::update(int position, bool init=false) {
    HorizontalSlider::_update(position, init);
}

void HorizontalSlider::_update(int position, bool init=false) {

    if(HorizontalSlider::_old_value!=position or not HorizontalSlider::_widget_created) {
        HorizontalSlider::_widget_created = true;
        HorizontalSlider::_old_value = position;

        if(_y == 0) {
            _y = _tft.height() - HorizontalSlider::_slider_height - 1;
        }

        // Clear the area to the left and right of the previous slider position
        if (HorizontalSlider::_current_position != -1) {
            int clearX = max(HorizontalSlider::_current_position, 0);
            int clearWidth = min(HorizontalSlider::_slider_width + 2, _width - clearX);
            _tft.fillRect(_x + clearX, _y, clearWidth, HorizontalSlider::_slider_height, _config.TFT_BACKGROUND);
        }

        // Calculate the slider position based on the provided value
        int sliderX = map(position, 0, 255, 0, (_width - HorizontalSlider::_slider_width));

        // Draw the slider track as vertical lines
        for (int i = 0; i <= _width; i += HorizontalSlider::_line_track_distance) {
            _tft.drawFastVLine(_x + i, _y, HorizontalSlider::_slider_height, TFT_DARKGREY);
        }

        // Draw the slider knob as a rectangle
        if(!init) {
            _tft.drawRect(_x + sliderX, _y, HorizontalSlider::_slider_width, HorizontalSlider::_slider_height, TFT_WHITE);
        }

        // Update the previous slider position
        HorizontalSlider::_current_position = sliderX;
    }
}