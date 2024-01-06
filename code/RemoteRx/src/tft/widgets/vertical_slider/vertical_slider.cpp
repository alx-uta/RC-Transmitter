/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "vertical_slider.hpp"

VerticalSlider::VerticalSlider(
    Config & config, 
    TFT_eSPI & tft,
    int x,
    int y,
    int start_value,
    int end_value,
    int height,
    int margin_top,
    int track_width,
    int track_spacing
)
    :   _config(config),
        _tft(tft) {
            _x = x;
            _y = y;
            _start_value = start_value;
            _end_value = end_value;
            _height = height;
            _margin_top = margin_top;
            _track_width = track_width;
            _track_spacing = track_spacing;
        }

void VerticalSlider::init() {
    VerticalSlider::update(-1, true);
}

void VerticalSlider::update(int position) {
    VerticalSlider::_update(position, false);
}
void VerticalSlider::update(int position, bool init=false) {
    VerticalSlider::_update(position, init);
}

void VerticalSlider::_update(int position, bool init = false) {
    if(VerticalSlider::_old_value!=position or not VerticalSlider::_widget_created) {
        VerticalSlider::_widget_created = true;
        VerticalSlider::_old_value = position;

        /**
         * Clear the area above and below 
         * the previous slider position
         */
        if (VerticalSlider::_current_position != -1) {
            int clearY = max(
                VerticalSlider::_current_position, _margin_top
            );
            int clearHeight = min(
                _track_width,
                _height - clearY
            );
            _tft.fillRect(
                _x,
                clearY,
                _track_width,
                clearHeight,
                _config.TFT_BACKGROUND
            );
        }

        // Define the slider track dimensions
        int numSegments = (
            _height - _margin_top
        ) / _track_spacing + 1;

        // Calculate the slider position based on the provided value
        int sliderY = map(
            position,
            VerticalSlider::_start_value,
            VerticalSlider::_end_value,
            _margin_top,
            (_height - VerticalSlider::_slider_height)
        );

        // Draw the slider track as horizontal lines
        for (int i = 0; i < numSegments; i++) {
            int segmentY = _margin_top + i * VerticalSlider::_line_track_distance;
            _tft.drawFastHLine(_x, segmentY, _track_width, TFT_DARKGREY);
        }

        if(!init) {
            _tft.drawRect(
                _x,
                sliderY,
                _track_width,
                _slider_height,
                position == 0 and VerticalSlider::_start_value == 255 ? TFT_DARKGREY :  TFT_WHITE
            );
        }

        // Update the previous slider position
        VerticalSlider::_current_position = sliderY;
    }
}