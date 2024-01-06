/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "tx.hpp"

Tx::Tx(
        MCP3208& joystick,
        MCP3208& potentiometer,
        MCP23S17& rotaryRead,
        MCP23S17& switches,
        Rotary& leftRotary,
        Rotary& rightRotary,
        Config& config
    )
    :   _joystick(joystick), 
        _potentiometer(potentiometer),
        _rotaryRead(rotaryRead),
        _switches(switches),
        _leftRotary(leftRotary),
        _rightRotary(rightRotary),
        _config(config) {
            // Init the joystick with the default value
            this->joystick_default_value = _config.joystick_default_value;
        }

/**
 * Read and set the right values
 */
void Tx::readData() {
    this->joysticks();
    this->potentiometers();
    this->readMCP23S17();
}