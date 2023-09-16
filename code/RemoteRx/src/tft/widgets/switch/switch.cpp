/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "switch.hpp"

Switch::Switch(
    Config & config, 
    TFT_eSPI & tft,
    int x,
    int y,
    int index,
    int width = 16,
    int height = 20,
    int spacing = 5,
    bool display_off_box = false
)
    :   _config(config),
        _tft(tft) {
            _x = x;
            _y = y;
            _index = index;
            _width = width;
            _height = height;
            _spacing = spacing;
            _display_off_box = display_off_box;
        }

Switch::Switch(
    Config & config, 
    TFT_eSPI & tft,
    int x,
    int y,
    int index
)
    :   _config(config),
        _tft(tft) {
            _x = x;
            _y = y;
            _index = index;
            _width = 16;
            _height = 20;
            _spacing = 5;
            _display_off_box = false;
        }

void Switch::init() {
    Switch::update(0);
}

void Switch::update(int state) {
    if(state == Switch::_old_value and !Switch::_widget_created) {
        return;
    }

    Switch::_old_value = state;
    Switch::_widget_created = true;

    int x = _x + _index * (_width + _spacing);
    int y = _y;
    
    // Define colors for the "on" and "off" states
    uint16_t on_colour = _config.TFT_SWITCH_ON;
    uint16_t off_colour = _config.TFT_SWITCH_OFF;
    uint16_t disabled_colour = _config.TFT_SWITCH_DISABLED;
    
    // Determine the colors and borders based on the switch state
    uint16_t top_box_colour = state ? on_colour : disabled_colour;
    uint16_t top_box_border_colour = state ? on_colour : disabled_colour;
    
    uint16_t bottom_box_colour = state ? disabled_colour : off_colour;
    uint16_t bottom_box_border_colour = state ? disabled_colour : off_colour;

    // Draw the top box (represents "on" state)
    _tft.drawRect(x, y, _width, _height / 2, top_box_border_colour);
    _tft.fillRect(x + 2, y + 2, _width - 4, (_height / 2) - 4, top_box_colour);

    if(Switch::_display_off_box){
        // Draw the bottom box (represents "off" state)
        y += _height / 2 + 2; // Add a small spacing
        _tft.drawRect(_x, _y, _width, _height / 2, bottom_box_border_colour);
        _tft.fillRect(_x + 2, _y + 2, _width - 4, (_height / 2) - 4, bottom_box_colour);
    }
}