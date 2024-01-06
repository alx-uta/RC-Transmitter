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
    if (
        (percentage == BatteryIcon::_old_value && !BatteryIcon::_widget_created) or (
            abs(percentage - BatteryIcon::_old_value) <= 5
        )
    ) {
        return;
    }

    BatteryIcon::_old_value = percentage;
    BatteryIcon::_widget_created = true;

    // Set a default border
    int border_radius = 3;

    // Reduced height
    int height = BatteryIcon::_width / 2;

    // Choose the color based on the percentage range
    uint16_t fillColor = TFT_GREEN;

    // Calculate the inner width based on the percentage
    int innerWidth = map(
        percentage, 0, 100, 0, BatteryIcon::_width - 2 * border_radius
    );

    // Clear the right portion of the battery with the background color (TFT_BLACK)
    int clearWidth = BatteryIcon::_width - innerWidth - border_radius;
    _tft.fillRect(
        _x + innerWidth + 1, _y + border_radius, clearWidth, height - 2 * border_radius, TFT_BLACK
    );

    // Update the battery fill with the chosen color
    _tft.fillRect(
        _x + 3, _y + border_radius, innerWidth, height - 2 * border_radius, fillColor
    );

    // Draw battery outline
    _tft.drawRect(
        _x, _y, BatteryIcon::_width, height, TFT_WHITE
    );
}