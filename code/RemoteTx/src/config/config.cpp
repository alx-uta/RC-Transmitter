/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "config.hpp"

Config::Config (
    // Joystick General
    uint8_t joystick_default_value,
    uint8_t joystick_min_out,
    uint8_t joystick_max_out,

    // Left Joystick
    uint8_t left_joystick_drift_value_x,
    int left_joystick_min_value_x,
    int left_joystick_max_value_x,
    int left_joystick_middle_value_x,

    uint8_t left_joystick_drift_value_y,
    int left_joystick_min_value_y,
    int left_joystick_max_value_y,
    int left_joystick_middle_value_y,

    // Right Joystick
    uint8_t right_joystick_drift_value_x,
    int right_joystick_min_value_x,
    int right_joystick_max_value_x,
    int right_joystick_middle_value_x,

    uint8_t right_joystick_drift_value_y,
    int right_joystick_min_value_y,
    int right_joystick_max_value_y,
    int right_joystick_middle_value_y,

    // Potentiometers
    uint8_t pot_drift_value,
    uint8_t pot_min,
    int pot_max,
    uint8_t pot_out_max
) {
    // Joystick General
    Config::joystick_default_value = joystick_default_value;
    Config::joystick_min_out = joystick_min_out;
    Config::joystick_max_out = joystick_max_out;

    // Left Joystick
    Config::left_joystick_drift_value_x = left_joystick_drift_value_x;
    Config::left_joystick_min_value_x = left_joystick_min_value_x;
    Config::left_joystick_max_value_x = left_joystick_max_value_x;
    Config::left_joystick_middle_value_x = left_joystick_middle_value_x;

    Config::left_joystick_drift_value_y = left_joystick_drift_value_y;
    Config::left_joystick_min_value_y = left_joystick_min_value_y;
    Config::left_joystick_max_value_y = left_joystick_max_value_y;
    Config::left_joystick_middle_value_y = left_joystick_middle_value_y;

    // Right Joystick
    Config::right_joystick_drift_value_x = right_joystick_drift_value_x;
    Config::right_joystick_min_value_x = right_joystick_min_value_x;
    Config::right_joystick_max_value_x = right_joystick_max_value_x;
    Config::right_joystick_middle_value_x = right_joystick_middle_value_x;

    Config::right_joystick_drift_value_y = right_joystick_drift_value_y;
    Config::right_joystick_min_value_y = right_joystick_min_value_y;
    Config::right_joystick_max_value_y = right_joystick_max_value_y;
    Config::right_joystick_middle_value_y = right_joystick_middle_value_y;

    // Potentiometers
    Config::pot_drift_value = pot_drift_value;
    Config::pot_min = pot_min;
    Config::pot_max = pot_max;
    Config::pot_out_max = pot_out_max;
}
