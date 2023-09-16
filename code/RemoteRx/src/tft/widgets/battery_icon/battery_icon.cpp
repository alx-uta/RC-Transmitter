/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "battery_icon.hpp"

BatteryIcon::BatteryIcon(Config & config, TFT_eSPI & tft, int x, int y, int width)
    :   _config(config),
        _tft(tft) {
            _x = x;
            _y = y;
            _width = width;
        }

void BatteryIcon::init() {
    BatteryIcon::update(0);
}

void BatteryIcon::init(int percentage) {
    BatteryIcon::update(percentage);
}

void BatteryIcon::update(int percentage) {
    if(percentage == BatteryIcon::_old_value and !BatteryIcon::_widget_created) {
        return;
    }

    BatteryIcon::_old_value = percentage;
    BatteryIcon::_widget_created = true;

    // Set a default border
    int border_radius = 3;

    // Reduced height
    int height = BatteryIcon::_width / 2;

    // Choose the color based on the percentage range
    uint16_t fillColor;

    if (percentage <= 0) {
        // If percentage is 0 or negative, draw an empty battery (disabled)
        _tft.drawRect(_x, _y, BatteryIcon::_width, height, TFT_RED);
        return;
    } else if (percentage <= 25) {
        // Red for 0-25%
        fillColor = TFT_RED;
    } else if (percentage <= 50) {
        // Yellow for 26-50%
        fillColor = TFT_YELLOW;
    } else {
        // Green for above 50%
        fillColor = TFT_GREEN;
    }

    // Calculate the inner width based on the percentage
    int innerWidth = map(
        percentage, 0, 100, 0, BatteryIcon::_width - 2 * border_radius
    );

    // Draw battery fill with the chosen color
    _tft.fillRect(
        _x + 1, _y + border_radius, innerWidth, height - 2 * border_radius, fillColor
    );

    // Draw battery outline
    _tft.drawRect(
        _x, _y, BatteryIcon::_width, height, TFT_WHITE
    );
}